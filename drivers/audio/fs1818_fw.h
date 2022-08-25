/****************************************************************************
 * drivers/audio/fs1818_fw.h
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

#ifndef __DRIVERS_AUDIO_FS1818_FW_H__
#define __DRIVERS_AUDIO_FS1818_FW_H__

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Type Declarations
 ****************************************************************************/

struct fs1818_reg
{
  uint8_t reg;
  uint16_t value;
};

/****************************************************************************
 * Private Data
 ****************************************************************************/

static const uint32_t fs1818_fw_music[] =
{
  0x0015f558, 0x00f6f074, 0x0012a697, 0x00090f88,
  0x00ef65ea, 0x00167fa9, 0x00f54518, 0x0015180c,
  0x000abae4, 0x00ec666c, 0x00177569, 0x00fde257,
  0x00165d1d, 0x00021da9, 0x00ea2f5f, 0x000b7465,
  0x00fe27b9, 0x001ff751, 0x0001d847, 0x00ec926c,
  0x00106553, 0x00e9d287, 0x001e2330, 0x0004749c,
  0x00eb2e30, 0x00083cc9, 0x00f8e028, 0x0016f3c8,
  0x00071fd4, 0x00e8d100, 0x0017b5fb, 0x00f89664,
  0x0017b5fb, 0x00076738, 0x00e89787, 0x00174804,
  0x00fb2145, 0x0015da3a, 0x0004debb, 0x00eadb9b,
  0x0017c65e, 0x00f87122, 0x0017c65e, 0x00078f9a,
  0x00e871eb, 0x0017c65e, 0x00f87122, 0x0017c65e,
  0x00078f9a, 0x00e871eb, 0x000801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x000801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x001c0504, 0x00195bff, 0x001801da, 0x00e6a401,
  0x00050a50, 0x00eab596, 0x001801da, 0x00180165,
  0x001824af, 0x0018131a, 0x001801da, 0x00180165,
  0x001824af, 0x0018131a, 0x00195bff, 0x001801da,
  0x00e6a401, 0x00050a50, 0x00eab596, 0x001801da,
  0x00180165, 0x001824af, 0x0018131a, 0x001801da,
  0x00180165, 0x001824af, 0x0018131a, 0x00195bff,
  0x001801da, 0x00e6a401, 0x00050a50, 0x00eab596,
  0x001801da, 0x00180165, 0x001824af, 0x0018131a,
  0x001801da, 0x00180165, 0x001824af, 0x0018131a,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da
};

static const uint32_t fs1818_fw_voice[] =
{
  0x000801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x000801da, 0x001801da, 0x001801da,
  0x001801da, 0x001801da, 0x000801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x000801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x000801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x000801da, 0x001801da, 0x001801da,
  0x001801da, 0x001801da, 0x000801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x000801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x0017c65e, 0x00f87122, 0x0017c65e, 0x00078f9a,
  0x00e871eb, 0x0017c65e, 0x00f87122, 0x0017c65e,
  0x00078f9a, 0x00e871eb, 0x000801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x000801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x001c0504, 0x00195bff, 0x001801da, 0x00e6a401,
  0x00050a50, 0x00eab596, 0x001801da, 0x00180165,
  0x001824af, 0x0018131a, 0x001801da, 0x00180165,
  0x001824af, 0x0018131a, 0x00195bff, 0x001801da,
  0x00e6a401, 0x00050a50, 0x00eab596, 0x001801da,
  0x00180165, 0x001824af, 0x0018131a, 0x001801da,
  0x00180165, 0x001824af, 0x0018131a, 0x00195bff,
  0x001801da, 0x00e6a401, 0x00050a50, 0x00eab596,
  0x001801da, 0x00180165, 0x001824af, 0x0018131a,
  0x001801da, 0x00180165, 0x001824af, 0x0018131a,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da
};

static const uint32_t fs1818_fw_spk_model[] =
{
  0x005801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x00176f17, 0x00fade34, 0x0015cf3d,
  0x000521c8, 0x00eac396, 0x0017d310, 0x00f93cb0,
  0x0016f640, 0x0006c34c, 0x00e93446, 0x000801da,
  0x00f90897, 0x0016fedd, 0x0006f769, 0x00e90123,
  0x00e801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x00e801da, 0x001801da, 0x001801da,
  0x001801da, 0x001801da, 0x000801da, 0x00176f17,
  0x00fade34, 0x0015cf3d, 0x000521c8, 0x00eac396,
  0x0017d310, 0x00f93cb0, 0x0016f640, 0x0006c34c,
  0x00e93446, 0x000801da, 0x00f90897, 0x0016fedd,
  0x0006f769, 0x00e90123, 0x00e801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x00e801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x000801da
};

static const uint32_t fs1818_fw_spk_model_voice[] =
{
  0x005801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x00176f17, 0x00fade34, 0x0015cf3d,
  0x000521c8, 0x00eac396, 0x0017d310, 0x00f93cb0,
  0x0016f640, 0x0006c34c, 0x00e93446, 0x000801da,
  0x00f90897, 0x0016fedd, 0x0006f769, 0x00e90123,
  0x00e801da, 0x001801da, 0x001801da, 0x001801da,
  0x001801da, 0x00e801da, 0x001801da, 0x001801da,
  0x001801da, 0x001801da, 0x000801da, 0x00176f17,
  0x00fade34, 0x0015cf3d, 0x000521c8, 0x00eac396,
  0x0017d310, 0x00f93cb0, 0x0016f640, 0x0006c34c,
  0x00e93446, 0x000801da, 0x00f90897, 0x0016fedd,
  0x0006f769, 0x00e90123, 0x00e801da, 0x001801da,
  0x001801da, 0x001801da, 0x001801da, 0x00e801da,
  0x001801da, 0x001801da, 0x001801da, 0x001801da,
  0x000801da
};

static const struct fs1818_reg fs1818_reg_music[] =
{
  { .reg = 0xa6,  .value = 0x00f0 },
  { .reg = 0xa2,  .value = 0x01da },
  { .reg = 0xa3,  .value = 0x0008 },
  { .reg = 0xa8,  .value = 0x00bd },
  { .reg = 0xa7,  .value = 0x0004 },
  { .reg = 0xaa,  .value = 0x00af },
  { .reg = 0xa9,  .value = 0x02d8 },
  { .reg = 0xad,  .value = 0x007a },
  { .reg = 0xa1,  .value = 0x1812 },
  { .reg = 0x8a,  .value = 0x0100 },
  { .reg = 0x8b,  .value = 0x0000 },
  { .reg = 0xc0,  .value = 0x19ee },
  { .reg = 0x08,  .value = 0x00e5 },
  { .reg = 0xcf,  .value = 0x0028 },
  { .reg = 0xd3,  .value = 0x0100 },
  { .reg = 0x06,  .value = 0xff00 },
  { .reg = 0xcd,  .value = 0x180c },  /* M24:9dB M6:4.5dB */
};

static const struct fs1818_reg fs1818_reg_voice[] =
{
  { .reg = 0xa6,  .value = 0x00f0 },
  { .reg = 0xa2,  .value = 0x01da },
  { .reg = 0xa3,  .value = 0x0008 },
  { .reg = 0xa8,  .value = 0x00bd },
  { .reg = 0xa7,  .value = 0x0004 },
  { .reg = 0xaa,  .value = 0x00af },
  { .reg = 0xa9,  .value = 0x02d8 },
  { .reg = 0xad,  .value = 0x007a },
  { .reg = 0xa1,  .value = 0x1812 },
  { .reg = 0x8a,  .value = 0x0100 },
  { .reg = 0x8b,  .value = 0x0000 },
  { .reg = 0xc0,  .value = 0x19ee },
  { .reg = 0x08,  .value = 0x00e5 },
  { .reg = 0xcf,  .value = 0x0028 },
  { .reg = 0xd3,  .value = 0x0000 },
  { .reg = 0x06,  .value = 0xff00 },
  { .reg = 0xcd,  .value = 0x180c },  /* M24:9dB M6:4.5dB */
};

#endif