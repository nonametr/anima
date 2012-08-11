/*
Navicat MySQL Data Transfer

Source Server         : jedgames.com
Source Server Version : 50522
Source Host           : jedgames.com:3306
Source Database       : ho_gs

Target Server Type    : MYSQL
Target Server Version : 50522
File Encoding         : 65001

Date: 2012-05-17 20:36:33
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `user_data`
-- ----------------------------
DROP TABLE IF EXISTS `user_data`;
CREATE TABLE `user_data` (
  `uid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `social_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `social_net_id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `first_name` varchar(25) NOT NULL DEFAULT 'not set',
  `last_name` varchar(25) NOT NULL DEFAULT 'not set',
  `nick_name` varchar(25) NOT NULL DEFAULT 'not set',
  `sex` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `music` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `sound` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `is_admin` tinyint(4) unsigned NOT NULL DEFAULT '0',
  `last_join_utime` int(11) unsigned NOT NULL,
  `registration_utime` int(11) unsigned NOT NULL,
  `language` tinyint(4) unsigned NOT NULL,
  `invited_friends_count` smallint(6) unsigned NOT NULL,
  `avatar` mediumtext NOT NULL,
  `max_energy_endtime` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `db_id` tinyint(3) unsigned NOT NULL DEFAULT '1',
  `active` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `last_activity` int(10) unsigned NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=52 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_data
-- ----------------------------
INSERT INTO `user_data` VALUES ('0', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('1', '3597077', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', 'tst', '0', '1', '1', '0');
INSERT INTO `user_data` VALUES ('2', '4756198', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '1', '0');
INSERT INTO `user_data` VALUES ('3', '166170586', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '1', '0');
INSERT INTO `user_data` VALUES ('4', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('5', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('6', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('7', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('8', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('9', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('10', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('11', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('12', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('13', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('14', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('15', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('16', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('17', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('18', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('19', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('20', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('21', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('22', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('23', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('24', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('25', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('26', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('27', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('28', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('29', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('30', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('31', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('32', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('33', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('34', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('35', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('36', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('37', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('38', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('39', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('40', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('41', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('42', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('43', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('44', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('45', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('46', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('47', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('48', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('49', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('50', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');
INSERT INTO `user_data` VALUES ('51', '0', '0', 'not set', 'not set', 'not set', '0', '0', '0', '0', '0', '0', '0', '0', '', '0', '1', '0', '0');

-- ----------------------------
-- Table structure for `user_data_objects`
-- ----------------------------
DROP TABLE IF EXISTS `user_data_objects`;
CREATE TABLE `user_data_objects` (
  `uid` int(10) unsigned NOT NULL AUTO_INCREMENT,
  `globals` mediumtext NOT NULL,
  `collections` mediumtext NOT NULL,
  `req_collections` tinytext NOT NULL,
  `locations` mediumtext NOT NULL,
  `talents` mediumtext NOT NULL,
  `items` mediumtext NOT NULL,
  `bosses` mediumtext NOT NULL,
  `active_boss` mediumtext NOT NULL,
  `app_friends_data` mediumtext NOT NULL,
  `events` mediumtext NOT NULL,
  `active` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `boss_strikes` mediumtext NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_data_objects
-- ----------------------------
INSERT INTO `user_data_objects` VALUES ('0', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '1', '');
INSERT INTO `user_data_objects` VALUES ('1', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '1', '');
INSERT INTO `user_data_objects` VALUES ('2', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '1', '');
INSERT INTO `user_data_objects` VALUES ('3', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '1', '');
INSERT INTO `user_data_objects` VALUES ('4', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('5', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('6', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('7', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('8', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('9', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('10', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('11', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('12', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('13', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('14', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('15', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('16', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('17', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('18', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('19', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('20', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('21', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('22', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('23', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('24', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('25', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('26', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('27', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('28', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('29', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('30', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('31', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('32', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('33', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('34', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('35', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('36', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('37', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('38', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('39', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('40', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('41', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('42', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('43', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('44', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('45', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('46', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('47', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('48', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('49', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');
INSERT INTO `user_data_objects` VALUES ('50', '[{\"id\":1, \"count\":1000 }, {\"id\":2, \"count\":1},{\"id\":3, \"count\":10000},{\"id\":4,\"count\":100000},{\"id\":5, \"count\":1},{\"id\":6, \"count\":100}]', '', '', '', '', '', '', '', '', '', '0', '');

-- ----------------------------
-- Table structure for `user_data_private`
-- ----------------------------
DROP TABLE IF EXISTS `user_data_private`;
CREATE TABLE `user_data_private` (
  `uid` mediumint(9) unsigned NOT NULL AUTO_INCREMENT,
  `active_boss` mediumtext NOT NULL,
  `active` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_data_private
-- ----------------------------
INSERT INTO `user_data_private` VALUES ('0', '', '1');
INSERT INTO `user_data_private` VALUES ('1', '', '1');
INSERT INTO `user_data_private` VALUES ('2', '', '1');
INSERT INTO `user_data_private` VALUES ('3', '', '1');
INSERT INTO `user_data_private` VALUES ('4', '', '0');
INSERT INTO `user_data_private` VALUES ('5', '', '0');
INSERT INTO `user_data_private` VALUES ('6', '', '0');
INSERT INTO `user_data_private` VALUES ('7', '', '0');
INSERT INTO `user_data_private` VALUES ('8', '', '0');
INSERT INTO `user_data_private` VALUES ('9', '', '0');
INSERT INTO `user_data_private` VALUES ('10', '', '0');
INSERT INTO `user_data_private` VALUES ('11', '', '0');
INSERT INTO `user_data_private` VALUES ('12', '', '0');
INSERT INTO `user_data_private` VALUES ('13', '', '0');
INSERT INTO `user_data_private` VALUES ('14', '', '0');
INSERT INTO `user_data_private` VALUES ('15', '', '0');
INSERT INTO `user_data_private` VALUES ('16', '', '0');
INSERT INTO `user_data_private` VALUES ('17', '', '0');
INSERT INTO `user_data_private` VALUES ('18', '', '0');
INSERT INTO `user_data_private` VALUES ('19', '', '0');
INSERT INTO `user_data_private` VALUES ('20', '', '0');
INSERT INTO `user_data_private` VALUES ('21', '', '0');
INSERT INTO `user_data_private` VALUES ('22', '', '0');
INSERT INTO `user_data_private` VALUES ('23', '', '0');
INSERT INTO `user_data_private` VALUES ('24', '', '0');
INSERT INTO `user_data_private` VALUES ('25', '', '0');
INSERT INTO `user_data_private` VALUES ('26', '', '0');
INSERT INTO `user_data_private` VALUES ('27', '', '0');
INSERT INTO `user_data_private` VALUES ('28', '', '0');
INSERT INTO `user_data_private` VALUES ('29', '', '0');
INSERT INTO `user_data_private` VALUES ('30', '', '0');
INSERT INTO `user_data_private` VALUES ('31', '', '0');
INSERT INTO `user_data_private` VALUES ('32', '', '0');
INSERT INTO `user_data_private` VALUES ('33', '', '0');
INSERT INTO `user_data_private` VALUES ('34', '', '0');
INSERT INTO `user_data_private` VALUES ('35', '', '0');
INSERT INTO `user_data_private` VALUES ('36', '', '0');
INSERT INTO `user_data_private` VALUES ('37', '', '0');
INSERT INTO `user_data_private` VALUES ('38', '', '0');
INSERT INTO `user_data_private` VALUES ('39', '', '0');
INSERT INTO `user_data_private` VALUES ('40', '', '0');
INSERT INTO `user_data_private` VALUES ('41', '', '0');
INSERT INTO `user_data_private` VALUES ('42', '', '0');
INSERT INTO `user_data_private` VALUES ('43', '', '0');
INSERT INTO `user_data_private` VALUES ('44', '', '0');
INSERT INTO `user_data_private` VALUES ('45', '', '0');
INSERT INTO `user_data_private` VALUES ('46', '', '0');
INSERT INTO `user_data_private` VALUES ('47', '', '0');
INSERT INTO `user_data_private` VALUES ('48', '', '0');
INSERT INTO `user_data_private` VALUES ('49', '', '0');
INSERT INTO `user_data_private` VALUES ('50', '', '0');

-- ----------------------------
-- Table structure for `user_rating_data`
-- ----------------------------
DROP TABLE IF EXISTS `user_rating_data`;
CREATE TABLE `user_rating_data` (
  `uid` int(10) unsigned NOT NULL,
  `social_id` bigint(20) unsigned NOT NULL,
  `lvl` mediumint(8) unsigned NOT NULL,
  `exp` int(11) NOT NULL,
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of user_rating_data
-- ----------------------------
INSERT INTO `user_rating_data` VALUES ('0', '0', '1', '1');
