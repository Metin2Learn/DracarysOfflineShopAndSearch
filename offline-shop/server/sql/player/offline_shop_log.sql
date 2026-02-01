/*
Navicat MySQL Data Transfer

Source Server         : alman
Source Server Version : 50651
Source Host           : 167.86.90.34:3306
Source Database       : player

Target Server Type    : MYSQL
Target Server Version : 50651
File Encoding         : 65001

Date: 2021-05-23 02:41:38
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for offline_shop_log
-- ----------------------------
DROP TABLE IF EXISTS `offline_shop_log`;
CREATE TABLE `offline_shop_log` (
  `owner_id` int(11) NOT NULL DEFAULT '0',
  `target` varchar(32) CHARACTER SET utf8 COLLATE utf8_turkish_ci NOT NULL,
  `time` varchar(32) CHARACTER SET latin1 NOT NULL,
  `itemvnum` int(11) NOT NULL DEFAULT '0',
  `itemcount` int(11) NOT NULL DEFAULT '0',
  `price` int(11) NOT NULL DEFAULT '0',
  `item_id` int(11) unsigned NOT NULL DEFAULT '0',
  `name` varchar(49) NOT NULL DEFAULT '^',
  `perma` smallint(2) NOT NULL,
  `pos` smallint(5) unsigned NOT NULL DEFAULT '0',
  `socket0` int(10) unsigned NOT NULL DEFAULT '0',
  `socket1` int(10) unsigned NOT NULL DEFAULT '0',
  `socket2` int(10) unsigned NOT NULL DEFAULT '0',
  `socket3` int(10) unsigned NOT NULL DEFAULT '0',
  `socket4` int(10) NOT NULL DEFAULT '0',
  `socket5` int(10) NOT NULL DEFAULT '0',
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
  `applytype0` tinyint(4) NOT NULL DEFAULT '0',
  `transmutation` int(11) NOT NULL DEFAULT '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin5 ROW_FORMAT=DYNAMIC;
SET FOREIGN_KEY_CHECKS=1;
