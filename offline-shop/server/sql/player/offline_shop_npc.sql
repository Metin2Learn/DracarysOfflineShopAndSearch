/*
Navicat MySQL Data Transfer

Source Server         : alman
Source Server Version : 50651
Source Host           : 167.86.90.34:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-05-23 02:41:44
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for offline_shop_npc
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_npc`;
CREATE TABLE `offline_shop_npc` (
  `owner_id` int(11) NOT NULL DEFAULT '0',
  `owner_name` varchar(32) NOT NULL DEFAULT 'NONE',
  `sign` varchar(32) CHARACTER SET utf8 COLLATE utf8_turkish_ci NOT NULL DEFAULT 'NONE',
  `x` int(11) NOT NULL DEFAULT '0',
  `y` int(11) NOT NULL DEFAULT '0',
  `z` int(11) NOT NULL DEFAULT '0',
  `mapindex` int(11) NOT NULL DEFAULT '0',
  `type` int(11) NOT NULL DEFAULT '0',
  `channel` int(11) NOT NULL DEFAULT '0',
  `slotflag` bigint(40) NOT NULL DEFAULT '0',
  `time` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`owner_id`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin1 ROW_FORMAT=DYNAMIC;
SET FOREIGN_KEY_CHECKS=1;
