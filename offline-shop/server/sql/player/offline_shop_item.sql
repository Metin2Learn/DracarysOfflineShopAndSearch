/*
Navicat MySQL Data Transfer

Source Server         : alman
Source Server Version : 50651
Source Host           : 167.86.90.34:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-05-23 02:41:31
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for offline_shop_item
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_item`;
CREATE TABLE `offline_shop_item` (
  `id` int(11) unsigned NOT NULL DEFAULT '0',
  `owner_id` int(11) unsigned NOT NULL DEFAULT '0',
  `pos` int(11) unsigned NOT NULL DEFAULT '0',
  `count` int(11) unsigned NOT NULL DEFAULT '0',
  `name` varchar(49) NOT NULL DEFAULT '^',
  `perma` smallint(2) NOT NULL DEFAULT '0',
  `vnum` int(11) unsigned NOT NULL DEFAULT '0',
  `socket0` int(11) unsigned NOT NULL DEFAULT '0',
  `socket1` int(11) unsigned NOT NULL DEFAULT '0',
  `socket2` int(11) unsigned NOT NULL DEFAULT '0',
  `socket3` int(11) unsigned NOT NULL DEFAULT '0',
  `socket4` int(11) NOT NULL DEFAULT '0',
  `socket5` int(11) NOT NULL DEFAULT '0',
  `attrtype0` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue0` smallint(6) NOT NULL DEFAULT '0',
  `attrtype1` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue1` smallint(6) NOT NULL DEFAULT '0',
  `attrtype2` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue2` smallint(6) NOT NULL DEFAULT '0',
  `attrtype3` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue3` smallint(6) NOT NULL DEFAULT '0',
  `attrtype4` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue4` smallint(6) NOT NULL DEFAULT '0',
  `attrtype5` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue5` smallint(6) NOT NULL DEFAULT '0',
  `attrtype6` tinyint(4) NOT NULL DEFAULT '0',
  `attrvalue6` smallint(6) NOT NULL DEFAULT '0',
  `price` bigint(33) NOT NULL DEFAULT '0',
  `status` int(11) NOT NULL DEFAULT '0',
  `ownername` varchar(24) CHARACTER SET latin5 COLLATE latin5_bin NOT NULL DEFAULT 'NONAME',
  `buyername` varchar(24) CHARACTER SET latin5 COLLATE latin5_bin NOT NULL DEFAULT 'NONAME',
  `transmutation` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`),
  KEY `owner_id_idx` (`owner_id`) USING BTREE,
  KEY `item_vnum_index` (`vnum`) USING BTREE
) ENGINE=MyISAM DEFAULT CHARSET=latin5 ROW_FORMAT=DYNAMIC;
SET FOREIGN_KEY_CHECKS=1;
