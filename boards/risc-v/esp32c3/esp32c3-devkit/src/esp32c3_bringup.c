/****************************************************************************
 * boards/risc-v/esp32c3/esp32c3-devkit/src/esp32c3_bringup.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <syslog.h>
#include <debug.h>
#include <stdio.h>

#include <nuttx/fs/fs.h>

#include "esp32c3_wlan.h"
#include "esp32c3_spiflash.h"
#include "esp32c3_partition.h"
#include "esp32c3-devkit.h"

#ifdef CONFIG_SPI
#  include "esp32c3_spi.h"
#endif

#ifdef CONFIG_ESP32C3_RT_TIMER
#  include "esp32c3_rt_timer.h"
#endif

#ifdef CONFIG_TIMER
#  include "esp32c3_tim_lowerhalf.h"
#endif

#include "esp32c3_rtc.h"

#ifdef CONFIG_RTC_DRIVER
#  include "esp32c3_rtc_lowerhalf.h"
#endif

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: esp32c3_init_wifi_storage
 *
 * Description:
 *   Initialization of saved Wi-Fi parameters
 *
 ****************************************************************************/

#ifdef CONFIG_ESP32C3_WIFI_SAVE_PARAM
static int esp32c3_init_wifi_storage(void)
{
  int ret;
  const char *path = "/dev/mtdblock1";
  FAR struct mtd_dev_s *mtd_part;

  mtd_part = esp32c3_spiflash_alloc_mtdpart();
  if (!mtd_part)
    {
      syslog(LOG_ERR, "ERROR: Failed to alloc MTD partition of SPI Flash\n");
      return -1;
    }

  ret = register_mtddriver(path, mtd_part, 0777, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to register MTD: %d\n", ret);
      return -1;
    }

  ret = nx_mount(path, CONFIG_ESP32C3_WIFI_FS_MOUNTPT, "spiffs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount the FS volume: %d\n", ret);
      return ret;
    }

  return 0;
}
#endif

/****************************************************************************
 * Name: esp32c3_bringup
 *
 * Description:
 *   Perform architecture-specific initialization
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=y :
 *     Called from board_late_initialize().
 *
 *   CONFIG_BOARD_LATE_INITIALIZE=n && CONFIG_LIB_BOARDCTL=y :
 *     Called from the NSH library
 *
 ****************************************************************************/

int esp32c3_bringup(void)
{
  int ret;

#ifdef CONFIG_FS_PROCFS
  /* Mount the procfs file system */

  ret = nx_mount(NULL, "/proc", "procfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount procfs at /proc: %d\n", ret);
    }
#endif

#ifdef CONFIG_FS_TMPFS
  /* Mount the tmpfs file system */

  ret = nx_mount(NULL, CONFIG_LIBC_TMPDIR, "tmpfs", 0, NULL);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to mount tmpfs at %s: %d\n",
             CONFIG_LIBC_TMPDIR, ret);
    }
#endif

#ifdef CONFIG_ESP32C3_SPIFLASH

#  ifdef CONFIG_ESP32C3_SPIFLASH_ENCRYPTION_TEST
  esp32c3_spiflash_encrypt_test();
#  endif

  ret = esp32c3_spiflash_init();
  if (ret)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize SPI Flash\n");
      return ret;
    }
#endif

#ifdef CONFIG_ESP32C3_PARTITION
  ret = esp32c3_partition_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize partition error=%d\n",
             ret);
      return ret;
    }
#endif

#ifdef CONFIG_DEV_GPIO
  ret = esp32c3_gpio_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize GPIO Driver: %d\n", ret);
      return ret;
    }
#endif

#if defined(CONFIG_SPI_DRIVER) && defined(CONFIG_ESP32C3_SPI2)
  ret = board_spidev_initialize(ESP32C3_SPI2);
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize SPI%d driver: %d\n",
             ESP32C3_SPI2, ret);
    }
#endif

#if defined(CONFIG_SPI_SLAVE_DRIVER) && defined(CONFIG_ESP32C3_SPI2)
  ret = board_spislavedev_initialize(ESP32C3_SPI2);
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize SPI%d Slave driver: %d\n",
             ESP32C3_SPI2, ret);
    }
#endif

#if defined(CONFIG_I2C_DRIVER)
  /* Configure I2C peripheral interfaces */

  ret = board_i2c_init();

  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize I2C driver: %d\n", ret);
    }
#endif

#ifdef CONFIG_SENSORS_BMP180
  /* Try to register BMP180 device in I2C0 */

  ret = board_bmp180_initialize(0, 0);

  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize BMP180 "
                       "Driver for I2C0: %d\n", ret);
      return ret;
    }
#endif

#ifdef CONFIG_WATCHDOG
  /* Configure watchdog timer */

  ret = board_wdt_init();
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to initialize watchdog drivers: %d\n",
             ret);
    }
#endif

/* First, register the timer drivers and let timer 1 for oneshot
 * if it is enabled.
 */

#ifdef CONFIG_TIMER

#if defined(CONFIG_ESP32C3_TIMER0) && !defined(CONFIG_ESP32C3_RT_TIMER)
  ret = esp32c3_timer_initialize("/dev/timer0", TIMER0);
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to initialize timer driver: %d\n",
             ret);
    }
#endif

#if defined(CONFIG_ESP32C3_TIMER1) && !defined(CONFIG_ONESHOT)
  ret = esp32c3_timer_initialize("/dev/timer1", TIMER1);
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to initialize timer driver: %d\n",
             ret);
    }
#endif

#endif /* CONFIG_TIMER */

  /* Now register one oneshot driver */

#if defined(CONFIG_ONESHOT) && defined(CONFIG_ESP32C3_TIMER1)

  ret = board_oneshot_init(ONESHOT_TIMER, ONESHOT_RESOLUTION_US);
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: board_oneshot_init() failed: %d\n", ret);
    }

#endif /* CONFIG_ONESHOT */

#ifdef CONFIG_ESP32C3_RT_TIMER
  ret = esp32c3_rt_timer_init();
  if (ret < 0)
    {
      syslog(LOG_ERR, "Failed to initialize RT timer: %d\n", ret);
    }
#endif

#ifdef CONFIG_ESP32C3_WIRELESS

#ifdef CONFIG_ESP32C3_WIFI_SAVE_PARAM
  ret = esp32c3_init_wifi_storage();
  if (ret)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize Wi-Fi storage\n");
      return ret;
    }
#endif

#ifdef CONFIG_NET
#ifdef ESP32C3_WLAN_HAS_STA
  ret = esp32c3_wlan_sta_initialize();
  if (ret)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize Wi-Fi station\n");
      return ret;
    }
#endif

#ifdef ESP32C3_WLAN_HAS_SOFTAP
  ret = esp32c3_wlan_softap_initialize();
  if (ret)
    {
      syslog(LOG_ERR, "ERROR: Failed to initialize Wi-Fi softAP\n");
      return ret;
    }
#endif
#endif

#endif

#ifdef CONFIG_ESP32C3_LEDC
  ret = esp32c3_pwm_setup();
  if (ret < 0)
    {
      syslog(LOG_ERR, "ERROR: esp32c3_pwm_setup() failed: %d\n", ret);
    }
#endif /* CONFIG_ESP32C3_LEDC */

#ifdef CONFIG_ESP32C3_ADC
  ret = board_adc_init();
  if (ret)
    {
      syslog(LOG_ERR, "ERROR: board_adc_init() failed: %d\n", ret);
      return ret;
    }
#endif /* CONFIG_ESP32C3_ADC */

#ifdef CONFIG_RTC_DRIVER
  /* Instantiate the ESP32-C3 RTC driver */

  ret = esp32c3_rtc_driverinit();
  if (ret < 0)
    {
      syslog(LOG_ERR,
             "ERROR: Failed to Instantiate the RTC driver: %d\n", ret);
    }
#endif

  /* If we got here then perhaps not all initialization was successful, but
   * at least enough succeeded to bring-up NSH with perhaps reduced
   * capabilities.
   */

  UNUSED(ret);
  return OK;
}
