/*
Navicat MySQL Data Transfer

Source Server         : jedgames.com
Source Server Version : 50522
Source Host           : jedgames.com:3306
Source Database       : ho_main

Target Server Type    : MYSQL
Target Server Version : 50522
File Encoding         : 65001

Date: 2012-05-17 20:36:08
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `db_desc`
-- ----------------------------
DROP TABLE IF EXISTS `db_desc`;
CREATE TABLE `db_desc` (
  `db_id` tinyint(3) unsigned NOT NULL,
  `name` varchar(25) NOT NULL,
  `ip` varchar(25) NOT NULL,
  `port` varchar(25) NOT NULL,
  `user` varchar(25) NOT NULL,
  `password` varchar(25) NOT NULL,
  `charset` varchar(25) NOT NULL,
  `active` tinyint(3) unsigned NOT NULL DEFAULT '1',
  PRIMARY KEY (`db_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of db_desc
-- ----------------------------
INSERT INTO `db_desc` VALUES ('0', 'NOP_DB', '', '', '', '', '', '0');
INSERT INTO `db_desc` VALUES ('1', 'ho_gs', '88.198.52.86', '3306', 'nonametr', 'power282', 'utf8', '1');
INSERT INTO `db_desc` VALUES ('2', 'ho_gs', '88.198.52.86', '3306', 'nonametr', 'power282', 'utf8', '1');

-- ----------------------------
-- Table structure for `dict_boss`
-- ----------------------------
DROP TABLE IF EXISTS `dict_boss`;
CREATE TABLE `dict_boss` (
  `object` varchar(25) NOT NULL,
  `hp` smallint(5) unsigned NOT NULL,
  `withdraw_obj` varchar(255) NOT NULL,
  `need_obj` varchar(25) NOT NULL,
  `win_reward_obj` varchar(25) NOT NULL,
  PRIMARY KEY (`object`),
  KEY `ml_name` (`object`) USING BTREE,
  KEY `need_obj` (`need_obj`) USING BTREE,
  KEY `give_obj` (`win_reward_obj`) USING BTREE,
  KEY `withdraw_obj` (`withdraw_obj`) USING BTREE,
  CONSTRAINT `dict_boss_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_boss_ibfk_2` FOREIGN KEY (`win_reward_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_boss_ibfk_3` FOREIGN KEY (`withdraw_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `need_obj_boss_fk` FOREIGN KEY (`need_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_boss
-- ----------------------------
INSERT INTO `dict_boss` VALUES ('boss_1', '1000', 'boss_1_wdraw', 'boss_1_fight_need', 'boss_1_reward_pack');
INSERT INTO `dict_boss` VALUES ('boss_2', '2000', 'boss_2_wdraw', 'boss_2_fight_need', 'boss_2_reward_pack');
INSERT INTO `dict_boss` VALUES ('boss_3', '3000', 'boss_3_wdraw', 'boss_3_fight_need', 'boss_3_reward_pack');
INSERT INTO `dict_boss` VALUES ('boss_4', '4000', 'boss_4_wdraw', 'boss_4_fight_need', 'boss_4_reward_pack');
INSERT INTO `dict_boss` VALUES ('boss_5', '5000', 'boss_5_wdraw', 'boss_5_fight_need', 'boss_5_reward_pack');
INSERT INTO `dict_boss` VALUES ('boss_6', '6000', 'boss_6_wdraw', 'boss_6_fight_need', 'boss_6_reward_pack');

-- ----------------------------
-- Table structure for `dict_boss_strike`
-- ----------------------------
DROP TABLE IF EXISTS `dict_boss_strike`;
CREATE TABLE `dict_boss_strike` (
  `object` varchar(25) NOT NULL,
  `damage_type` set('PERCENTAGE','PURE') NOT NULL,
  `damage` smallint(5) unsigned NOT NULL,
  `cooldown` mediumint(8) unsigned NOT NULL,
  PRIMARY KEY (`object`),
  CONSTRAINT `dict_boss_strike_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_boss_strike
-- ----------------------------
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_1', 'PURE', '100', '0');
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_2', 'PURE', '200', '0');
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_3', 'PURE', '300', '0');
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_4', 'PURE', '400', '0');
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_5', 'PURE', '500', '0');
INSERT INTO `dict_boss_strike` VALUES ('boss_strike_6', 'PURE', '600', '0');

-- ----------------------------
-- Table structure for `dict_drop_chance`
-- ----------------------------
DROP TABLE IF EXISTS `dict_drop_chance`;
CREATE TABLE `dict_drop_chance` (
  `object` varchar(25) NOT NULL,
  `in_pack_obj` varchar(25) NOT NULL,
  `chance_max_10000` smallint(6) unsigned NOT NULL DEFAULT '10000',
  PRIMARY KEY (`object`,`in_pack_obj`),
  KEY `object` (`object`),
  KEY `in_pack_obj` (`in_pack_obj`),
  CONSTRAINT `dict_drop_chance_ibfk_1` FOREIGN KEY (`object`, `in_pack_obj`) REFERENCES `dict_pack` (`object`, `in_pack_obj`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_drop_chance
-- ----------------------------
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_win_pack_1', 'coll_monkey1', '3000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_win_pack_1', 'coll_monkey2', '3000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_1_wdraw_3', 'energy', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_win_pack_1', 'coll_key1', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_win_pack_1', 'coll_lantern2', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_win_pack_1', 'coll_lantern3', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_2_wdraw_1', 'energy', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_win_pack_1', 'coll_chest2', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_win_pack_1', 'coll_key3', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_win_pack_1', 'coll_pipe3', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_3_wdraw_2', 'energy', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_win_pack_1', 'coll_glass1', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_win_pack_1', 'coll_key2', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_win_pack_1', 'coll_key4', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_4_wdraw_1', 'energy', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_win_pack_1', 'coll_cap2', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_win_pack_1', 'coll_chest4', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_win_pack_1', 'coll_pipe4', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_5_wdraw_1', 'energy', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_lose_pack', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_lose_pack', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_win_pack_1', 'coll_clock1', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_win_pack_1', 'coll_clock3', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_win_pack_1', 'coll_goblet2', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_win_pack_1', 'exp', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_rew_win_pack_1', 'money', '10000');
INSERT INTO `dict_drop_chance` VALUES ('location_6_wdraw_1', 'energy', '10000');

-- ----------------------------
-- Table structure for `dict_exchange`
-- ----------------------------
DROP TABLE IF EXISTS `dict_exchange`;
CREATE TABLE `dict_exchange` (
  `object` varchar(25) NOT NULL,
  `object_count` smallint(5) unsigned NOT NULL DEFAULT '1',
  `exchange_object` varchar(25) NOT NULL,
  `exchange_object_count` smallint(5) unsigned NOT NULL,
  `slot_id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`slot_id`),
  KEY `object` (`object`),
  KEY `exchange_obj` (`exchange_object`),
  CONSTRAINT `dict_exchange_ibfk_1` FOREIGN KEY (`exchange_object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `object_shop_fk` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=17 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_exchange
-- ----------------------------
INSERT INTO `dict_exchange` VALUES ('energy', '10', 'money', '1', '1');
INSERT INTO `dict_exchange` VALUES ('energy', '50', 'money', '4', '2');
INSERT INTO `dict_exchange` VALUES ('energy', '100', 'money', '7', '3');
INSERT INTO `dict_exchange` VALUES ('bullets', '1', 'gold', '1', '4');
INSERT INTO `dict_exchange` VALUES ('bullets', '5', 'gold', '4', '5');
INSERT INTO `dict_exchange` VALUES ('coll_monkey_el', '1', 'coll_monkey_pack', '1', '6');
INSERT INTO `dict_exchange` VALUES ('coll_pipe_el', '1', 'coll_pipe_pack', '1', '8');
INSERT INTO `dict_exchange` VALUES ('coll_lantern_el', '1', 'coll_lantern_pack', '1', '9');
INSERT INTO `dict_exchange` VALUES ('coll_key_el', '1', 'coll_key_pack', '1', '10');
INSERT INTO `dict_exchange` VALUES ('coll_chest_el', '1', 'coll_chest_pack', '1', '11');
INSERT INTO `dict_exchange` VALUES ('coll_knife_el', '1', 'coll_knife_pack', '1', '12');
INSERT INTO `dict_exchange` VALUES ('coll_cap_el', '1', 'coll_cap_pack', '1', '13');
INSERT INTO `dict_exchange` VALUES ('coll_clock_el', '1', 'coll_clock_pack', '1', '14');
INSERT INTO `dict_exchange` VALUES ('coll_goblet_el', '1', 'coll_goblet_pack', '1', '15');
INSERT INTO `dict_exchange` VALUES ('coll_glass_el', '1', 'coll_glass_pack', '1', '16');

-- ----------------------------
-- Table structure for `dict_give`
-- ----------------------------
DROP TABLE IF EXISTS `dict_give`;
CREATE TABLE `dict_give` (
  `object` varchar(25) NOT NULL,
  `if_object_count` mediumint(8) unsigned NOT NULL DEFAULT '0',
  `give` varchar(25) NOT NULL,
  `give_count` mediumint(8) unsigned NOT NULL DEFAULT '1',
  `record_id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`record_id`),
  KEY `object` (`object`),
  KEY `give` (`give`),
  CONSTRAINT `dict_give_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_give_ibfk_2` FOREIGN KEY (`give`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=1006 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_give
-- ----------------------------
INSERT INTO `dict_give` VALUES ('exp', '100', 'lvl', '1', '1');
INSERT INTO `dict_give` VALUES ('exp', '300', 'lvl', '1', '2');
INSERT INTO `dict_give` VALUES ('exp', '500', 'lvl', '1', '3');
INSERT INTO `dict_give` VALUES ('exp', '800', 'lvl', '1', '4');
INSERT INTO `dict_give` VALUES ('lvl', '1', 'gold', '1', '1001');
INSERT INTO `dict_give` VALUES ('lvl', '2', 'gold', '2', '1002');
INSERT INTO `dict_give` VALUES ('lvl', '3', 'gold', '3', '1003');
INSERT INTO `dict_give` VALUES ('lvl', '4', 'gold', '4', '1004');
INSERT INTO `dict_give` VALUES ('lvl', '5', 'gold', '5', '1005');

-- ----------------------------
-- Table structure for `dict_lang`
-- ----------------------------
DROP TABLE IF EXISTS `dict_lang`;
CREATE TABLE `dict_lang` (
  `object` varchar(25) NOT NULL,
  `ru` varchar(255) NOT NULL,
  `en` varchar(255) NOT NULL,
  PRIMARY KEY (`object`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_lang
-- ----------------------------
INSERT INTO `dict_lang` VALUES ('boss_1', 'Первый босс', 'First boss');
INSERT INTO `dict_lang` VALUES ('boss_1_fight_need', 'Предметы необходимые для борьбы с 1 боссом', 'Items needed for 1-st boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_1_image', '/bosses/images/redneck_full.png', '/bosses/images/redneck_full.png');
INSERT INTO `dict_lang` VALUES ('boss_1_key', 'Ключ для атаки на злодея', 'Key for villant\'s atack');
INSERT INTO `dict_lang` VALUES ('boss_1_key_image', '/bosses/images/key_1.png', '/bosses/images/key_1.png');
INSERT INTO `dict_lang` VALUES ('boss_1_reward_pack', 'Награда за победу над 1-м боссом', 'Reward for winning the 1st boss');
INSERT INTO `dict_lang` VALUES ('boss_1_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_2', 'Второй босс', 'Second boss');
INSERT INTO `dict_lang` VALUES ('boss_2_fight_need', 'Предметы необходимые для борьбы со 2 боссом', 'Items needed for 2-nd boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_2_image', '/bosses/images/bandit_full.png', '/bosses/images/bandit_full.png');
INSERT INTO `dict_lang` VALUES ('boss_2_key', 'Ключ для атаки на злодея', 'Key for villants atack');
INSERT INTO `dict_lang` VALUES ('boss_2_key_image', '/bosses/images/key_2.png', '/bosses/images/key_2.png');
INSERT INTO `dict_lang` VALUES ('boss_2_reward_pack', 'Награда за победу над 2-м боссом', 'Reward for winning the 2nd boss');
INSERT INTO `dict_lang` VALUES ('boss_2_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_3', 'Третий босс', 'Third boss');
INSERT INTO `dict_lang` VALUES ('boss_3_fight_need', 'Предметы необходимые для борьбы с 3-м боссом', 'Items needed for 3-rd boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_3_image', '/bosses/images/bouncer_full.png', '/bosses/images/bouncer_full.png');
INSERT INTO `dict_lang` VALUES ('boss_3_key', 'Ключ для атаки на злодея', 'Key for villants atack');
INSERT INTO `dict_lang` VALUES ('boss_3_key_image', '/bosses/images/key_3.png', '/bosses/images/key_3.png');
INSERT INTO `dict_lang` VALUES ('boss_3_reward_pack', 'Награда за победу над 3-м боссом', 'Reward for winning the 3rd boss');
INSERT INTO `dict_lang` VALUES ('boss_3_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_4', 'Четвертый босс', 'Forth boss');
INSERT INTO `dict_lang` VALUES ('boss_4_fight_need', 'Предметы необходимые для борьбы с 4-м боссом', 'Items needed for 4-th boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_4_image', '/bosses/images/don_lukas_full.png', '/bosses/images/don_lukas_full.png');
INSERT INTO `dict_lang` VALUES ('boss_4_key', 'Ключ для атаки на злодея', 'Key for villants atack');
INSERT INTO `dict_lang` VALUES ('boss_4_key_image', '/bosses/images/key_4.png', '/bosses/images/key_4.png');
INSERT INTO `dict_lang` VALUES ('boss_4_reward_pack', 'Награда за победу над 4-м боссом', 'Reward for winning the 4th boss');
INSERT INTO `dict_lang` VALUES ('boss_4_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_5', 'Пятый босс', 'Fith boss');
INSERT INTO `dict_lang` VALUES ('boss_5_fight_need', 'Предметы необходимые для борьбы с 5-м боссом', 'Items needed for 5-th boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_5_image', '/bosses/images/sirchik_full.png', '/bosses/images/sirchik_full.png');
INSERT INTO `dict_lang` VALUES ('boss_5_key', 'Ключ для атаки на злодея', 'Key for villants atack');
INSERT INTO `dict_lang` VALUES ('boss_5_key_image', '/bosses/images/key_5.png', '/bosses/images/key_5.png');
INSERT INTO `dict_lang` VALUES ('boss_5_reward_pack', 'Награда за победу над 5-м боссом', 'Reward for winning the 5th boss');
INSERT INTO `dict_lang` VALUES ('boss_5_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_6', 'Шестой босс', 'Sixth boss');
INSERT INTO `dict_lang` VALUES ('boss_6_fight_need', 'Предметы необходимые для борьбы с 4-м боссом', 'Items needed for 6-th boss fighting');
INSERT INTO `dict_lang` VALUES ('boss_6_image', '/bosses/images/pygmy_full.png', '/bosses/images/pygmy_full.png');
INSERT INTO `dict_lang` VALUES ('boss_6_key', 'Ключ для атаки на злодея', 'Key for villants atack');
INSERT INTO `dict_lang` VALUES ('boss_6_key_image', '/bosses/images/key_6.png', '/bosses/images/key_6.png');
INSERT INTO `dict_lang` VALUES ('boss_6_reward_pack', 'Награда за победу над 6-м боссом', 'Reward for winning the 6th boss');
INSERT INTO `dict_lang` VALUES ('boss_6_wdraw', 'Вам необходимо затратить для атаки на босса', 'For bosses atack you need');
INSERT INTO `dict_lang` VALUES ('boss_strike_1', 'Удар по боссу 1', 'Strike to the Boss 1');
INSERT INTO `dict_lang` VALUES ('boss_strike_1_desc', 'Описание ударов по боссу 1', 'Description of the Boss strike 1');
INSERT INTO `dict_lang` VALUES ('boss_strike_1_img', '/bosses/images/boss_strike_1.png', '/bosses/images/boss_strike_1.png');
INSERT INTO `dict_lang` VALUES ('boss_strike_2', 'Удар по боссу 2', 'Strike to the Boss 2');
INSERT INTO `dict_lang` VALUES ('boss_strike_2_desc', 'Описание ударов по боссу 2', 'Description of the Boss strike 2');
INSERT INTO `dict_lang` VALUES ('boss_strike_2_img', '/bosses/images/boss_strike_2.png', '/bosses/images/boss_strike_2.png');
INSERT INTO `dict_lang` VALUES ('boss_strike_3', 'Удар по боссу 3', 'Strike to the Boss 3');
INSERT INTO `dict_lang` VALUES ('boss_strike_3_desc', 'Описание ударов по боссу 3', 'Description of the Boss strike 3');
INSERT INTO `dict_lang` VALUES ('boss_strike_3_img', '/bosses/images/boss_strike_3.png', '/bosses/images/boss_strike_3.png');
INSERT INTO `dict_lang` VALUES ('boss_strike_4', 'Удар по боссу 4', 'Strike to the Boss 4');
INSERT INTO `dict_lang` VALUES ('boss_strike_4_desc', 'Описание ударов по боссу 4', 'Description of the Boss strike 4');
INSERT INTO `dict_lang` VALUES ('boss_strike_4_img', '/bosses/images/boss_strike_4.png', '/bosses/images/boss_strike_4.png');
INSERT INTO `dict_lang` VALUES ('boss_strike_5', 'Удар по боссу 5', 'Strike to the Boss 5');
INSERT INTO `dict_lang` VALUES ('boss_strike_5_desc', 'Описание ударов по боссу 5', 'Description of the Boss strike 5');
INSERT INTO `dict_lang` VALUES ('boss_strike_5_img', '/bosses/images/boss_strike_5.png', '/bosses/images/boss_strike_5.png');
INSERT INTO `dict_lang` VALUES ('boss_strike_6', 'Удар по боссу 6', 'Strike to the Boss 6');
INSERT INTO `dict_lang` VALUES ('boss_strike_6_desc', 'Описание ударов по боссу 6', 'Description of the Boss strike 6');
INSERT INTO `dict_lang` VALUES ('boss_strike_6_img', '/bosses/images/boss_strike_6.png', '/bosses/images/boss_strike_6.png');
INSERT INTO `dict_lang` VALUES ('bullets', 'Пули', 'Bullets');
INSERT INTO `dict_lang` VALUES ('bullets_desc', 'Описание для чего нужны пули', 'Bullets description');
INSERT INTO `dict_lang` VALUES ('bullets_image', '/common/images/bullets.png', '/common/images/bullets.png');
INSERT INTO `dict_lang` VALUES ('coll_cap1', 'Шляпа Крестьянина', 'Cap of peasant');
INSERT INTO `dict_lang` VALUES ('coll_cap1_desc', 'Элемент коллекции - \"Царская Корона\"', 'Part of the collection \"Royal crown\"');
INSERT INTO `dict_lang` VALUES ('coll_cap1_image', '/collections/cap/cap1.png', '/collections/cap/cap1.png');
INSERT INTO `dict_lang` VALUES ('coll_cap2', 'Шляпа исследователя', 'Cap of explorer');
INSERT INTO `dict_lang` VALUES ('coll_cap2_desc', 'Элемент коллекции - \"Царская Корона\"', 'Part of the collection \"Royal crown\"');
INSERT INTO `dict_lang` VALUES ('coll_cap2_image', '/collections/cap/cap2.png', '/collections/cap/cap2.png');
INSERT INTO `dict_lang` VALUES ('coll_cap3', 'Шляпа дворянина', 'Cap of gentleman');
INSERT INTO `dict_lang` VALUES ('coll_cap3_desc', 'Элемент коллекции - \"Царская Корона\"', 'Part of the collection \"Royal crown\"');
INSERT INTO `dict_lang` VALUES ('coll_cap3_image', '/collections/cap/cap3.png', '/collections/cap/cap3.png');
INSERT INTO `dict_lang` VALUES ('coll_cap4', 'Дамская шляпка', 'Bonnet');
INSERT INTO `dict_lang` VALUES ('coll_cap4_desc', 'Элемент коллекции - \"Царская Корона\"', 'Part of the collection \"Royal crown\"');
INSERT INTO `dict_lang` VALUES ('coll_cap4_image', '/collections/cap/cap4.png', '/collections/cap/cap4.png');
INSERT INTO `dict_lang` VALUES ('coll_cap_el', 'Царская Корона', 'Royal crown');
INSERT INTO `dict_lang` VALUES ('coll_cap_el_desc', 'Основной элемент коллекции - \"Царская Корона\"', 'Main part of the collection \"Royal crown\"');
INSERT INTO `dict_lang` VALUES ('coll_cap_el_image', '/collections/cap/cap_el.png', '/collections/cap/cap_el.png');
INSERT INTO `dict_lang` VALUES ('coll_chest1', 'Старый сундук', 'Old chest');
INSERT INTO `dict_lang` VALUES ('coll_chest1_desc', 'Элемент коллекции - \"Сундук желаний\"', 'Part of the collection \"Chest of Desires\"');
INSERT INTO `dict_lang` VALUES ('coll_chest1_image', '/collections/chest/chest1.png', '/collections/chest/chest1.png');
INSERT INTO `dict_lang` VALUES ('coll_chest2', 'Ящик принадлежностей', 'Drawer accessories');
INSERT INTO `dict_lang` VALUES ('coll_chest2_desc', 'Элемент коллекции - \"Сундук желаний\"', 'Part of the collection \"Chest of Desires\"');
INSERT INTO `dict_lang` VALUES ('coll_chest2_image', '/collections/chest/chest2.png', '/collections/chest/chest2.png');
INSERT INTO `dict_lang` VALUES ('coll_chest3', 'Чемоданчик', 'Suitcase');
INSERT INTO `dict_lang` VALUES ('coll_chest3_desc', 'Элемент коллекции - \"Сундук желаний\"', 'Part of the collection \"Chest of Desires\"');
INSERT INTO `dict_lang` VALUES ('coll_chest3_image', '/collections/chest/chest3.png', '/collections/chest/chest3.png');
INSERT INTO `dict_lang` VALUES ('coll_chest4', 'Большой сундук', 'Large chest');
INSERT INTO `dict_lang` VALUES ('coll_chest4_desc', 'Элемент коллекции - \"Сундук желаний\"', 'Part of the collection \"Chest of Desires\"');
INSERT INTO `dict_lang` VALUES ('coll_chest4_image', '/collections/chest/chest4.png', '/collections/chest/chest4.png');
INSERT INTO `dict_lang` VALUES ('coll_chest_el', 'Сундук желаний', 'Chest of Desires');
INSERT INTO `dict_lang` VALUES ('coll_chest_el_desc', 'Основной элемент коллекции - \"Сундук желаний\"', 'Main part of the collection \"Chest of Desires\"');
INSERT INTO `dict_lang` VALUES ('coll_chest_el_image', '/collections/chest/chest_el.png', '/collections/chest/chest_el.png');
INSERT INTO `dict_lang` VALUES ('coll_clock1', 'Песочные часы', 'Hourglass');
INSERT INTO `dict_lang` VALUES ('coll_clock1_desc', 'Элемент коллекции - \"Золотые часы\"', 'Part of the collection \"Gold clock\"');
INSERT INTO `dict_lang` VALUES ('coll_clock1_image', '/collections/clock/clock1.png', '/collections/clock/clock1.png');
INSERT INTO `dict_lang` VALUES ('coll_clock2', 'Настольные часы', 'Desk clock');
INSERT INTO `dict_lang` VALUES ('coll_clock2_desc', 'Элемент коллекции - \"Золотые часы\"', 'Part of the collection \"Gold clock\"');
INSERT INTO `dict_lang` VALUES ('coll_clock2_image', '/collections/clock/clock2.png', '/collections/clock/clock2.png');
INSERT INTO `dict_lang` VALUES ('coll_clock3', 'Будильник', 'Alarm clock');
INSERT INTO `dict_lang` VALUES ('coll_clock3_desc', 'Элемент коллекции - \"Золотые часы\"', 'Part of the collection \"Gold clock\"');
INSERT INTO `dict_lang` VALUES ('coll_clock3_image', '/collections/clock/clock3.png', '/collections/clock/clock3.png');
INSERT INTO `dict_lang` VALUES ('coll_clock4', 'Антикварные часы', 'Antique clock');
INSERT INTO `dict_lang` VALUES ('coll_clock4_desc', 'Элемент коллекции - \"Золотые часы\"', 'Part of the collection \"Gold clock\"');
INSERT INTO `dict_lang` VALUES ('coll_clock4_image', '/collections/clock/clock4.png', '/collections/clock/clock4.png');
INSERT INTO `dict_lang` VALUES ('coll_clock_el', 'Золотые часы', 'Gold clock');
INSERT INTO `dict_lang` VALUES ('coll_clock_el_desc', 'Коллекция - \"Золотые часы\"', 'Collection \"Gold clock\"');
INSERT INTO `dict_lang` VALUES ('coll_clock_el_image', '/collections/clock/clock_el.png', '/collections/clock/clock_el.png');
INSERT INTO `dict_lang` VALUES ('coll_glass1', 'Обычные очки', 'Ordinary glasses');
INSERT INTO `dict_lang` VALUES ('coll_glass1_desc', 'Элемент коллекции - \"Очки сезона\"', 'Part of the collection \"Glasses of the Season\"');
INSERT INTO `dict_lang` VALUES ('coll_glass1_image', '/collections/glasses/glass1.png', '/collections/glasses/glass1.png');
INSERT INTO `dict_lang` VALUES ('coll_glass2', 'Очки ювелира', 'Glasses of jeweler');
INSERT INTO `dict_lang` VALUES ('coll_glass2_desc', 'Элемент коллекции - \"Очки сезона\"', 'Part of the collection \"Glasses of the Season\"');
INSERT INTO `dict_lang` VALUES ('coll_glass2_image', '/collections/glasses/glass2.png', '/collections/glasses/glass2.png');
INSERT INTO `dict_lang` VALUES ('coll_glass3', 'Очки банкира', 'Glasses of banker');
INSERT INTO `dict_lang` VALUES ('coll_glass3_desc', 'Элемент коллекции - \"Очки сезона\"', 'Part of the collection \"Glasses of the Season\"');
INSERT INTO `dict_lang` VALUES ('coll_glass3_image', '/collections/glasses/glass3.png', '/collections/glasses/glass3.png');
INSERT INTO `dict_lang` VALUES ('coll_glass4', 'Очки беглеца', 'Glasses of fugitive');
INSERT INTO `dict_lang` VALUES ('coll_glass4_desc', 'Элемент коллекции - \"Очки сезона\"', 'Part of the collection \"Glasses of the Season\"');
INSERT INTO `dict_lang` VALUES ('coll_glass4_image', '/collections/glasses/glass4.png', '/collections/glasses/glass4.png');
INSERT INTO `dict_lang` VALUES ('coll_glass_el', 'Очки сезона', 'Glasses of the Season');
INSERT INTO `dict_lang` VALUES ('coll_glass_el_desc', 'Коллекция - \"Очки сезона\"', 'Collection \"Glasses of the Season\"');
INSERT INTO `dict_lang` VALUES ('coll_glass_el_image', '/collections/glasses/glass_el.png', '/collections/glasses/glass_el.png');
INSERT INTO `dict_lang` VALUES ('coll_goblet1', 'Кубок воина', 'Goblet of Warrior');
INSERT INTO `dict_lang` VALUES ('coll_goblet1_desc', 'Элемент коллекции - \"Кубок славы\"', 'Part of the collection \"Goblet of Glory\"');
INSERT INTO `dict_lang` VALUES ('coll_goblet1_image', '/collections/goblet/goblet1.png', '/collections/goblet/goblet1.png');
INSERT INTO `dict_lang` VALUES ('coll_goblet2', 'Кубок победы', 'Goblet of Victory');
INSERT INTO `dict_lang` VALUES ('coll_goblet2_desc', 'Элемент коллекции - \"Кубок славы\"', 'Part of the collection \"Goblet of Glory\"');
INSERT INTO `dict_lang` VALUES ('coll_goblet2_image', '/collections/goblet/goblet2.png', '/collections/goblet/goblet2.png');
INSERT INTO `dict_lang` VALUES ('coll_goblet3', 'Кубок священника', 'Goblet of Priest');
INSERT INTO `dict_lang` VALUES ('coll_goblet3_desc', 'Элемент коллекции - \"Кубок славы\"', 'Part of the collection \"Goblet of Glory\"');
INSERT INTO `dict_lang` VALUES ('coll_goblet3_image', '/collections/goblet/goblet3.png', '/collections/goblet/goblet3.png');
INSERT INTO `dict_lang` VALUES ('coll_goblet4', 'Кубок рыцаря', 'Crusaders goblet');
INSERT INTO `dict_lang` VALUES ('coll_goblet4_desc', 'Элемент коллекции - \"Кубок славы\"', 'Part of the collection \"Goblet of Glory\"');
INSERT INTO `dict_lang` VALUES ('coll_goblet4_image', '/collections/goblet/goblet4.png', '/collections/goblet/goblet4.png');
INSERT INTO `dict_lang` VALUES ('coll_goblet_el', 'Кубок славы', 'Goblet of Glory');
INSERT INTO `dict_lang` VALUES ('coll_goblet_el_desc', 'Коллекция - \"Кубок славы\"', 'Collection \"Goblet of Glory\"');
INSERT INTO `dict_lang` VALUES ('coll_goblet_el_image', '/collections/goblet/goblet_el.png', '/collections/goblet/goblet_el.png');
INSERT INTO `dict_lang` VALUES ('coll_key1', 'Простой ключ', 'Simple key');
INSERT INTO `dict_lang` VALUES ('coll_key1_desc', 'Элемент коллекции - \"Магический ключ\"', 'Part of the collection \"Magic Key\"');
INSERT INTO `dict_lang` VALUES ('coll_key1_image', '/collections/key/key1.png', '/collections/key/key1.png');
INSERT INTO `dict_lang` VALUES ('coll_key2', 'Старый ключ', 'Old key');
INSERT INTO `dict_lang` VALUES ('coll_key2_desc', 'Элемент коллекции - \"Магический ключ\"', 'Part of the collection \"Magic Key\"');
INSERT INTO `dict_lang` VALUES ('coll_key2_image', '/collections/key/key2.png', '/collections/key/key2.png');
INSERT INTO `dict_lang` VALUES ('coll_key3', 'Новый ключ', 'New key');
INSERT INTO `dict_lang` VALUES ('coll_key3_desc', 'Элемент коллекции - \"Магический ключ\"', 'Part of the collection \"Magic Key\"');
INSERT INTO `dict_lang` VALUES ('coll_key3_image', '/collections/key/key3.png', '/collections/key/key3.png');
INSERT INTO `dict_lang` VALUES ('coll_key4', 'Позолоченный ключ', 'Gold-plated key');
INSERT INTO `dict_lang` VALUES ('coll_key4_desc', 'Элемент коллекции - \"Магический ключ\"', 'Part of the collection \"Magic Key\"');
INSERT INTO `dict_lang` VALUES ('coll_key4_image', '/collections/key/key4.png', '/collections/key/key4.png');
INSERT INTO `dict_lang` VALUES ('coll_key_el', 'Магический ключ', 'Magic Key');
INSERT INTO `dict_lang` VALUES ('coll_key_el_desc', 'Основной элемент коллекции - \"Магический ключ\"', 'Main part of the collection \"Magic Key\"');
INSERT INTO `dict_lang` VALUES ('coll_key_el_image', '/collections/key/key_el.png', '/collections/key/key_el.png');
INSERT INTO `dict_lang` VALUES ('coll_knife1', 'Перочинный нож', 'Old knife');
INSERT INTO `dict_lang` VALUES ('coll_knife1_desc', 'Элемент коллекции - \"Кинжал рыцаря\"', 'Part of the collection \"Dagger knight\"');
INSERT INTO `dict_lang` VALUES ('coll_knife1_image', '/collections/knife/knife1.png', '/collections/knife/knife1.png');
INSERT INTO `dict_lang` VALUES ('coll_knife2', 'Обычный нож', 'Drawer accessories');
INSERT INTO `dict_lang` VALUES ('coll_knife2_desc', 'Элемент коллекции - \"Кинжал рыцаря\"', 'Part of the collection \"Dagger knight\"');
INSERT INTO `dict_lang` VALUES ('coll_knife2_image', '/collections/knife/knife2.png', '/collections/knife/knife2.png');
INSERT INTO `dict_lang` VALUES ('coll_knife3', 'Большой нож', 'Suitcase');
INSERT INTO `dict_lang` VALUES ('coll_knife3_desc', 'Элемент коллекции - \"Кинжал рыцаря\"', 'Part of the collection \"Dagger knight\"');
INSERT INTO `dict_lang` VALUES ('coll_knife3_image', '/collections/knife/knife3.png', '/collections/knife/knife3.png');
INSERT INTO `dict_lang` VALUES ('coll_knife4', 'Кинжал', 'Large knife');
INSERT INTO `dict_lang` VALUES ('coll_knife4_desc', 'Элемент коллекции - \"Кинжал рыцаря\"', 'Part of the collection \"Dagger knight\"');
INSERT INTO `dict_lang` VALUES ('coll_knife4_image', '/collections/knife/knife4.png', '/collections/knife/knife4.png');
INSERT INTO `dict_lang` VALUES ('coll_knife_el', 'Кинжал рыцаря', 'Dagger knight');
INSERT INTO `dict_lang` VALUES ('coll_knife_el_desc', 'Основной элемент коллекции - \"Кинжал рыцаря\"', 'Main part of the collection \"Dagger knight\"');
INSERT INTO `dict_lang` VALUES ('coll_knife_el_image', '/collections/knife/knife_el.png', '/collections/knife/knife_el.png');
INSERT INTO `dict_lang` VALUES ('coll_lantern1', 'Керосин', 'Kerosene');
INSERT INTO `dict_lang` VALUES ('coll_lantern1_desc', 'Элемент коллекции - \"Фонарь\"', 'Part of the collection \"Lantern\"');
INSERT INTO `dict_lang` VALUES ('coll_lantern1_image', '/collections/lantern/lantern1.png', '/collections/lantern/lantern1.png');
INSERT INTO `dict_lang` VALUES ('coll_lantern2', 'Спички', 'Matches');
INSERT INTO `dict_lang` VALUES ('coll_lantern2_desc', 'Элемент коллекции - \"Фонарь\"', 'Part of the collection \"Lantern\"');
INSERT INTO `dict_lang` VALUES ('coll_lantern2_image', '/collections/lantern/lantern2.png', '/collections/lantern/lantern2.png');
INSERT INTO `dict_lang` VALUES ('coll_lantern3', 'Бечевка', 'Twine');
INSERT INTO `dict_lang` VALUES ('coll_lantern3_desc', 'Элемент коллекции - \"Фонарь\"', 'Part of the collection \"Lantern\"');
INSERT INTO `dict_lang` VALUES ('coll_lantern3_image', '/collections/lantern/lantern3.png', '/collections/lantern/lantern3.png');
INSERT INTO `dict_lang` VALUES ('coll_lantern4', 'Факел', 'Torch');
INSERT INTO `dict_lang` VALUES ('coll_lantern4_desc', 'Элемент коллекции - \"Фонарь\"', 'Part of the collection \"Lantern\"');
INSERT INTO `dict_lang` VALUES ('coll_lantern4_image', '/collections/lantern/lantern4.png', '/collections/lantern/lantern4.png');
INSERT INTO `dict_lang` VALUES ('coll_lantern_el', 'Фонарь', 'Lantern');
INSERT INTO `dict_lang` VALUES ('coll_lantern_el_desc', 'Основной элемент коллекции - \"Фонарь\"', 'Main part of the collection \"Lantern\"');
INSERT INTO `dict_lang` VALUES ('coll_lantern_el_image', '/collections/lantern/lantern_el.png', '/collections/lantern/lantern_el.png');
INSERT INTO `dict_lang` VALUES ('coll_monkey1', 'Зеленая обезьяна', 'Green Monkey');
INSERT INTO `dict_lang` VALUES ('coll_monkey1_desc', 'Элемент коллекции - \"Золотой идол обезьяны\"', 'Part of the collection \"Gold Monkey Idol\"');
INSERT INTO `dict_lang` VALUES ('coll_monkey1_image', '/collections/monkey/monkey1.png', '/collections/monkey/monkey1.png');
INSERT INTO `dict_lang` VALUES ('coll_monkey2', 'Синяя обезьяна', 'Blue Monkey');
INSERT INTO `dict_lang` VALUES ('coll_monkey2_desc', 'Элемент коллекции - \"Золотой идол обезьяны\"', 'Part of the collection \"Gold Monkey Idol\"');
INSERT INTO `dict_lang` VALUES ('coll_monkey2_image', '/collections/monkey/monkey2.png', '/collections/monkey/monkey2.png');
INSERT INTO `dict_lang` VALUES ('coll_monkey3', 'Желтая обезьяна', 'Yellow Monkey');
INSERT INTO `dict_lang` VALUES ('coll_monkey3_desc', 'Элемент коллекции - \"Золотой идол обезьяны\"', 'Part of the collection \"Gold Monkey Idol\"');
INSERT INTO `dict_lang` VALUES ('coll_monkey3_image', '/collections/monkey/monkey3.png', '/collections/monkey/monkey3.png');
INSERT INTO `dict_lang` VALUES ('coll_monkey4', 'Пурпурная обезьяна', 'Purple Monkey');
INSERT INTO `dict_lang` VALUES ('coll_monkey4_desc', 'Элемент коллекции - \"Золотой идол обезьяны\"', 'Part of the collection \"Gold Monkey Idol\"');
INSERT INTO `dict_lang` VALUES ('coll_monkey4_image', '/collections/monkey/monkey4.png', '/collections/monkey/monkey4.png');
INSERT INTO `dict_lang` VALUES ('coll_monkey_el', 'Золотой идол обезьяны', 'Green Monkey Idol');
INSERT INTO `dict_lang` VALUES ('coll_monkey_el_desc', 'Основной элемент коллекции - \"Золотой идол обезьяны\"', 'Main part of the collection \"Gold Monkey Idol\"');
INSERT INTO `dict_lang` VALUES ('coll_monkey_el_image', '/collections/monkey/monkey_el.png', '/collections/monkey/monkey_el.png');
INSERT INTO `dict_lang` VALUES ('coll_pipe1', 'Дешевая трубка', 'Cheap pipe');
INSERT INTO `dict_lang` VALUES ('coll_pipe1_desc', 'Элемент коллекции - \"Курительная трубка\"', 'Part of the collection \"Pipe\"');
INSERT INTO `dict_lang` VALUES ('coll_pipe1_image', '/collections/pipe/pipe1.png', '/collections/pipe/pipe1.png');
INSERT INTO `dict_lang` VALUES ('coll_pipe2', 'Обычная трубка', 'Normal pipe');
INSERT INTO `dict_lang` VALUES ('coll_pipe2_desc', 'Элемент коллекции - \"Курительная трубка\"', 'Part of the collection \"Pipe\"');
INSERT INTO `dict_lang` VALUES ('coll_pipe2_image', '/collections/pipe/pipe2.png', '/collections/pipe/pipe2.png');
INSERT INTO `dict_lang` VALUES ('coll_pipe3', 'Дорогая трубка', 'Expensive pipe');
INSERT INTO `dict_lang` VALUES ('coll_pipe3_desc', 'Элемент коллекции - \"Курительная трубка\"', 'Part of the collection \"Pipe\"');
INSERT INTO `dict_lang` VALUES ('coll_pipe3_image', '/collections/pipe/pipe3.png', '/collections/pipe/pipe3.png');
INSERT INTO `dict_lang` VALUES ('coll_pipe4', 'Элитная трубка', 'Elite pipe');
INSERT INTO `dict_lang` VALUES ('coll_pipe4_desc', 'Элемент коллекции - \"Курительная трубка\"', 'Part of the collection \"Pipe\"');
INSERT INTO `dict_lang` VALUES ('coll_pipe4_image', '/collections/pipe/pipe4.png', '/collections/pipe/pipe4.png');
INSERT INTO `dict_lang` VALUES ('coll_pipe_el', 'Курительная трубка', 'Pipe');
INSERT INTO `dict_lang` VALUES ('coll_pipe_el_desc', 'Основной элемент коллекции - \"Курительная трубка\"', 'Main part of the collection \"Pipe\"');
INSERT INTO `dict_lang` VALUES ('coll_pipe_el_image', '/collections/pipe/pipe_el.png', '/collections/pipe/pipe_el.png');
INSERT INTO `dict_lang` VALUES ('energy', 'Энергия', 'Energy');
INSERT INTO `dict_lang` VALUES ('energy_desc', 'описание для чего нужна энергия', 'description why you should use energy');
INSERT INTO `dict_lang` VALUES ('energy_image', '/common/images/energy.png', '/common/images/energy.png');
INSERT INTO `dict_lang` VALUES ('exp', 'Опыт', 'Expierense');
INSERT INTO `dict_lang` VALUES ('exp_desc', 'Описание для чего нужен опыт', 'Description why you must obtain exp');
INSERT INTO `dict_lang` VALUES ('exp_image', '/common/images/exp.png', '/common/images/exp.png');
INSERT INTO `dict_lang` VALUES ('gold', 'Реал', 'Gold');
INSERT INTO `dict_lang` VALUES ('gold_desc', 'Описание для чего нужен реал', 'Gold description');
INSERT INTO `dict_lang` VALUES ('gold_image', '/common/images/gold.png', '/common/images/gold.png');
INSERT INTO `dict_lang` VALUES ('location_1', 'Имя первой локации', 'Location 1 name');
INSERT INTO `dict_lang` VALUES ('location_1_counter', 'Прохождение локации 1', 'Location 1 progress');
INSERT INTO `dict_lang` VALUES ('location_1_desc', 'Описание первой локации', 'Description of the 1 location');
INSERT INTO `dict_lang` VALUES ('location_1_image', '/locations/images/ru/loc_1.png', '/locations/images/en/loc_1.png');
INSERT INTO `dict_lang` VALUES ('location_1_need', 'Требования для начала прохождения 1 локации', 'Requirements for the initial location');
INSERT INTO `dict_lang` VALUES ('location_1_need_desc', 'Описание требований для начала прохождения 1 локации', 'Requirements description for the initial location');
INSERT INTO `dict_lang` VALUES ('location_1_need_image', '/locations/images/ru/loc_1_need.png', '/locations/images/en/loc_1_need.png');
INSERT INTO `dict_lang` VALUES ('location_1_rew_lose', 'Награда за проигрыш в 1 локации', 'Award for the lose in 1 location');
INSERT INTO `dict_lang` VALUES ('location_1_rew_win', 'Награда за победу в 1 локации', 'Award for the win in 1 location');
INSERT INTO `dict_lang` VALUES ('location_1_swf', '/locations/swf/location1.swf', '/locations/swf/location1.swf');
INSERT INTO `dict_lang` VALUES ('location_1_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 1 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 1th location');
INSERT INTO `dict_lang` VALUES ('location_2', 'Имя 2 локации', 'Location 2 name');
INSERT INTO `dict_lang` VALUES ('location_2_counter', 'Прохождение локации 2', 'Location 2 progress');
INSERT INTO `dict_lang` VALUES ('location_2_desc', 'Описание 2 локации', 'Location 2 description');
INSERT INTO `dict_lang` VALUES ('location_2_image', '/locations/images/loc_2.png', '/locations/images/loc_2.png');
INSERT INTO `dict_lang` VALUES ('location_2_need', 'Требования для начала прохождения 2 локации', 'Requirements for 2 location');
INSERT INTO `dict_lang` VALUES ('location_2_need_desc', 'Описание требований для начала прохождения 2 локации', 'Requirements description for 2 location');
INSERT INTO `dict_lang` VALUES ('location_2_need_image', '/locations/images/loc_2_need.png', '/locations/images/loc_2_need.png');
INSERT INTO `dict_lang` VALUES ('location_2_rew_lose', 'Награда за проигрыш во 2 локации', 'Award for the lose in 2 location');
INSERT INTO `dict_lang` VALUES ('location_2_rew_win', 'Награда за победу во 2 локации', 'Award for the win in 2 location');
INSERT INTO `dict_lang` VALUES ('location_2_swf', '/locations/swf/location2.swf', '/locations/swf/location2.swf');
INSERT INTO `dict_lang` VALUES ('location_2_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 2 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 2th location');
INSERT INTO `dict_lang` VALUES ('location_3', 'Имя 3 локации', 'Location 3 name');
INSERT INTO `dict_lang` VALUES ('location_3_counter', 'Прохождение локации 3', 'Location 3 progress');
INSERT INTO `dict_lang` VALUES ('location_3_desc', 'Описание 3 локации', 'Location 3 description');
INSERT INTO `dict_lang` VALUES ('location_3_image', '/locations/images/loc_3.png', '/locations/images/loc_3.png');
INSERT INTO `dict_lang` VALUES ('location_3_need', 'Требования для начала прохождения 3 локации', 'Requirements for 3 location');
INSERT INTO `dict_lang` VALUES ('location_3_need_desc', 'Описание требований для начала прохождения 3 локации', 'Requirements description for 3 location');
INSERT INTO `dict_lang` VALUES ('location_3_need_image', '/locations/images/loc_3_need.png', '/locations/images/loc_3_need.png');
INSERT INTO `dict_lang` VALUES ('location_3_rew_lose', 'Награда за проигрыш в 3 локации', 'Award for the loss in 3 location');
INSERT INTO `dict_lang` VALUES ('location_3_rew_win', 'Награда за победу в 3 локации', 'Award for the win in 3 location');
INSERT INTO `dict_lang` VALUES ('location_3_swf', '/locations/swf/location3.swf', '/locations/swf/location3.swf');
INSERT INTO `dict_lang` VALUES ('location_3_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 3 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 3th location');
INSERT INTO `dict_lang` VALUES ('location_4', 'Имя 4 локации', 'Location 4 name');
INSERT INTO `dict_lang` VALUES ('location_4_counter', 'Прохождение локации 4', 'Location 4 progress');
INSERT INTO `dict_lang` VALUES ('location_4_desc', 'Описание 4 локации', 'Location 4 description');
INSERT INTO `dict_lang` VALUES ('location_4_image', '/locations/images/loc_4.png', '/locations/images/loc_4.png');
INSERT INTO `dict_lang` VALUES ('location_4_need', 'Требования для начала прохождения 4 локации', 'Requirements for 4 location');
INSERT INTO `dict_lang` VALUES ('location_4_need_desc', 'Описание требований для начала прохождения 4 локации', 'Requirements description for 4 location');
INSERT INTO `dict_lang` VALUES ('location_4_need_image', '/locations/images/loc_4_need.png', '/locations/images/loc_4_need.png');
INSERT INTO `dict_lang` VALUES ('location_4_rew_lose', 'Награда за проигрыш в 4 локации', 'Award for the loss in 4 location');
INSERT INTO `dict_lang` VALUES ('location_4_rew_win', 'Награда за победу в 4 локации', 'Award for the win in 4 location');
INSERT INTO `dict_lang` VALUES ('location_4_swf', '/locations/swf/location4.swf', '/locations/swf/location4.swf');
INSERT INTO `dict_lang` VALUES ('location_4_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 4 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 4th location');
INSERT INTO `dict_lang` VALUES ('location_5', 'Имя 5 локации', 'Location 5 name');
INSERT INTO `dict_lang` VALUES ('location_5_counter', 'Прохождение локации 5', 'Location 5 progress');
INSERT INTO `dict_lang` VALUES ('location_5_desc', 'Описание 5 локации', 'Location 5 description');
INSERT INTO `dict_lang` VALUES ('location_5_image', '/locations/images/loc_5.png', '/locations/images/loc_5.png');
INSERT INTO `dict_lang` VALUES ('location_5_need', 'Требования для начала прохождения 5 локации', 'Requirements for 5 location');
INSERT INTO `dict_lang` VALUES ('location_5_need_desc', 'Описание требований для начала прохождения 5 локации', 'Requirements description for 5 location');
INSERT INTO `dict_lang` VALUES ('location_5_need_image', '/locations/images/loc_5_need.png', '/locations/images/loc_5_need.png');
INSERT INTO `dict_lang` VALUES ('location_5_rew_lose', 'Награда за проигрыш в 5 локации', 'Award for the loss in 5 location');
INSERT INTO `dict_lang` VALUES ('location_5_rew_win', 'Награда за победу в 5 локации', 'Award for the win in 5 location');
INSERT INTO `dict_lang` VALUES ('location_5_swf', '/locations/swf/location5.swf', '/locations/swf/location5.swf');
INSERT INTO `dict_lang` VALUES ('location_5_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 5 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 5th location');
INSERT INTO `dict_lang` VALUES ('location_6', 'Имя 6 локации', 'Location 6 name');
INSERT INTO `dict_lang` VALUES ('location_6_counter', 'Прохождение локации 6', 'Location 6 progress');
INSERT INTO `dict_lang` VALUES ('location_6_desc', 'Описание 6 локации', 'Location 6 description');
INSERT INTO `dict_lang` VALUES ('location_6_image', '/locations/images/loc_6.png', '/locations/images/loc_6.png');
INSERT INTO `dict_lang` VALUES ('location_6_need', 'Требования для начала прохождения 6 локации', 'Requirements for 6 location');
INSERT INTO `dict_lang` VALUES ('location_6_need_desc', 'Описание требований для начала прохождения 6 локации', 'Requirements description for 6 location');
INSERT INTO `dict_lang` VALUES ('location_6_need_image', '/locations/images/loc_6_need.png', '/locations/images/loc_6_need.png');
INSERT INTO `dict_lang` VALUES ('location_6_rew_lose', 'Награда за проигрыш в 6 локации', 'Award for the loss in 6 location');
INSERT INTO `dict_lang` VALUES ('location_6_rew_win', 'Награда за победу в 6 локации', 'Award for the win in 6 location');
INSERT INTO `dict_lang` VALUES ('location_6_swf', '/locations/swf/location6.swf', '/locations/swf/location6.swf');
INSERT INTO `dict_lang` VALUES ('location_6_withdraw', 'Имя обьекта который нужно забрать у пользователя в начале прохождения 6 локации', 'Name of the object that you want to take away from the user at the beginning of the passage of 6th location');
INSERT INTO `dict_lang` VALUES ('location_level_1', 'Новичек', 'Novice');
INSERT INTO `dict_lang` VALUES ('location_level_2', 'Любитель', 'Fan');
INSERT INTO `dict_lang` VALUES ('location_level_3', 'Профессионал', 'Professinal');
INSERT INTO `dict_lang` VALUES ('location_level_4', 'Эксперт', 'Expert');
INSERT INTO `dict_lang` VALUES ('location_level_5', 'Гуру', 'Guru');
INSERT INTO `dict_lang` VALUES ('location_mode_dark', 'Темный режим', 'Dark Mode');
INSERT INTO `dict_lang` VALUES ('location_mode_drag', 'Режим наложения предметов для выполнения условий их поиска', 'Drag objects');
INSERT INTO `dict_lang` VALUES ('location_mode_flash', 'Режим молний и вспышек', 'Lights mode');
INSERT INTO `dict_lang` VALUES ('location_mode_flip', 'Режим перевернутая комната', 'Flipped room');
INSERT INTO `dict_lang` VALUES ('location_mode_ghost', 'Режим пропадающих предметов', 'Hidden objects');
INSERT INTO `dict_lang` VALUES ('location_mode_night', 'Режим ночного видения', 'Night Mode');
INSERT INTO `dict_lang` VALUES ('location_mode_oneword', 'Режим поиска по одному слову', '');
INSERT INTO `dict_lang` VALUES ('location_mode_position', 'Вариант расположения предметов', '');
INSERT INTO `dict_lang` VALUES ('location_mode_random', 'Число случайных предметов', '');
INSERT INTO `dict_lang` VALUES ('location_mode_shadow', 'Режим поиска предметов по силуэтам', '');
INSERT INTO `dict_lang` VALUES ('location_mode_shuffletext', 'Режим перемешивающихся букв при поиске предметов', '');
INSERT INTO `dict_lang` VALUES ('location_mode_smog', 'Режим дымовой шашки', '');
INSERT INTO `dict_lang` VALUES ('location_mode_timestep', 'Режим скоростного поиска предметов по 10 сек', '');
INSERT INTO `dict_lang` VALUES ('lvl', 'Уровень', 'Level');
INSERT INTO `dict_lang` VALUES ('lvl_desc', 'Описание уровня', 'Level Description');
INSERT INTO `dict_lang` VALUES ('lvl_image', 'Картинка локации', 'Location Image');
INSERT INTO `dict_lang` VALUES ('money', 'Деньги', 'Money');
INSERT INTO `dict_lang` VALUES ('money_desc', 'Бриллианты. Реальная валюта.', 'Brilliants');
INSERT INTO `dict_lang` VALUES ('money_image', '/common/images/brilliants.png', '/common/images/brilliants.png');
INSERT INTO `dict_lang` VALUES ('NULL', 'НУЛЛ ОБДЖЕКТ', 'NULL OBJECT');

-- ----------------------------
-- Table structure for `dict_location`
-- ----------------------------
DROP TABLE IF EXISTS `dict_location`;
CREATE TABLE `dict_location` (
  `object` varchar(25) NOT NULL,
  `max_duration` smallint(5) unsigned NOT NULL,
  `need_obj` varchar(25) NOT NULL,
  `withdraw_obj` varchar(25) NOT NULL,
  `lose_reward_obj` varchar(25) NOT NULL,
  `win_reward_obj` varchar(25) NOT NULL,
  `lvl` tinyint(4) NOT NULL,
  `options_obj` varchar(25) NOT NULL,
  PRIMARY KEY (`lvl`,`object`),
  KEY `lose_reward_item` (`lose_reward_obj`) USING BTREE,
  KEY `win_reward_item` (`win_reward_obj`) USING BTREE,
  KEY `need_unlock_item` (`need_obj`) USING BTREE,
  KEY `withdraw_obj` (`withdraw_obj`),
  KEY `object` (`object`),
  KEY `options_obj` (`options_obj`),
  CONSTRAINT `dict_location_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_location_ibfk_2` FOREIGN KEY (`withdraw_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_location_ibfk_3` FOREIGN KEY (`options_obj`) REFERENCES `dict_object` (`object`),
  CONSTRAINT `lose_reward_obj_fk` FOREIGN KEY (`lose_reward_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `need_obj_obj_fk` FOREIGN KEY (`need_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `win_reward_obj_fk` FOREIGN KEY (`win_reward_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_location
-- ----------------------------
INSERT INTO `dict_location` VALUES ('location_1', '140', 'location_1_need_1', 'location_1_wdraw_1', 'location_1_rew_lose_pack', 'location_1_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_2', '140', 'location_2_need_1', 'location_2_wdraw_1', 'location_2_rew_lose_pack', 'location_2_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_3', '140', 'location_3_need_1', 'location_3_wdraw_1', 'location_3_rew_lose_pack', 'location_3_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_4', '140', 'location_4_need_1', 'location_4_wdraw_1', 'location_4_rew_lose_pack', 'location_4_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_5', '140', 'location_5_need_1', 'location_5_wdraw_1', 'location_5_rew_lose_pack', 'location_5_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_6', '140', 'location_6_need_1', 'location_6_wdraw_1', 'location_6_rew_lose_pack', 'location_6_rew_win_pack_1', '1', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_1', '130', 'location_1_need_2', 'location_1_wdraw_2', 'location_1_rew_lose_pack', 'location_1_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_2', '130', 'location_2_need_2', 'location_2_wdraw_2', 'location_2_rew_lose_pack', 'location_2_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_3', '130', 'location_3_need_2', 'location_3_wdraw_2', 'location_3_rew_lose_pack', 'location_3_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_4', '130', 'location_4_need_2', 'location_4_wdraw_2', 'location_4_rew_lose_pack', 'location_4_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_5', '130', 'location_5_need_2', 'location_5_wdraw_2', 'location_5_rew_lose_pack', 'location_5_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_6', '130', 'location_6_need_2', 'location_6_wdraw_2', 'location_6_rew_lose_pack', 'location_6_rew_win_pack_2', '2', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_1', '120', 'location_1_need_3', 'location_1_wdraw_3', 'location_1_rew_lose_pack', 'location_1_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_2', '120', 'location_2_need_3', 'location_2_wdraw_3', 'location_2_rew_lose_pack', 'location_2_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_3', '120', 'location_3_need_3', 'location_3_wdraw_3', 'location_3_rew_lose_pack', 'location_3_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_4', '120', 'location_4_need_3', 'location_4_wdraw_3', 'location_4_rew_lose_pack', 'location_4_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_5', '120', 'location_5_need_3', 'location_5_wdraw_3', 'location_5_rew_lose_pack', 'location_5_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_6', '120', 'location_6_need_3', 'location_6_wdraw_3', 'location_6_rew_lose_pack', 'location_6_rew_win_pack_3', '3', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_1', '110', 'location_1_need_4', 'location_1_wdraw_4', 'location_1_rew_lose_pack', 'location_1_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_2', '110', 'location_2_need_4', 'location_2_wdraw_4', 'location_2_rew_lose_pack', 'location_2_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_3', '110', 'location_3_need_4', 'location_3_wdraw_4', 'location_3_rew_lose_pack', 'location_3_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_4', '110', 'location_4_need_4', 'location_4_wdraw_4', 'location_4_rew_lose_pack', 'location_4_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_5', '110', 'location_5_need_4', 'location_5_wdraw_4', 'location_5_rew_lose_pack', 'location_5_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_6', '110', 'location_6_need_4', 'location_6_wdraw_4', 'location_6_rew_lose_pack', 'location_6_rew_win_pack_4', '4', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_1', '100', 'location_1_need_5', 'location_1_wdraw_5', 'location_1_rew_lose_pack', 'location_1_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_2', '100', 'location_2_need_5', 'location_2_wdraw_5', 'location_2_rew_lose_pack', 'location_2_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_3', '100', 'location_3_need_5', 'location_3_wdraw_5', 'location_3_rew_lose_pack', 'location_3_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_4', '100', 'location_4_need_5', 'location_4_wdraw_5', 'location_4_rew_lose_pack', 'location_4_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_5', '100', 'location_5_need_5', 'location_5_wdraw_5', 'location_5_rew_lose_pack', 'location_5_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');
INSERT INTO `dict_location` VALUES ('location_6', '100', 'location_6_need_5', 'location_6_wdraw_5', 'location_6_rew_lose_pack', 'location_6_rew_win_pack_5', '5', 'location_1_rew_win_pack_1');

-- ----------------------------
-- Table structure for `dict_message`
-- ----------------------------
DROP TABLE IF EXISTS `dict_message`;
CREATE TABLE `dict_message` (
  `object` varchar(5) NOT NULL,
  `ru` varchar(255) NOT NULL,
  `en` varchar(255) NOT NULL,
  PRIMARY KEY (`object`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_message
-- ----------------------------
INSERT INTO `dict_message` VALUES ('1', 'Обьект с этим id не найден в словаре', 'Dict obj not found');
INSERT INTO `dict_message` VALUES ('10', 'Ошибка дисериализации обьектов БД', 'DB objects deserialization error');
INSERT INTO `dict_message` VALUES ('1000', 'Обьект не может быть разблокирован условия не выполнены', 'Unlock condition fail');
INSERT INTO `dict_message` VALUES ('1001', 'Локация уже в работе', 'Location allready in work');
INSERT INTO `dict_message` VALUES ('1002', 'Невозможно получить награду за прохождение локации', 'Location cant finish');
INSERT INTO `dict_message` VALUES ('1003', 'Локация завернена не успешно', 'Location lose');
INSERT INTO `dict_message` VALUES ('1004', 'Уже идет бой с боссом', 'Boss fight allready in progress');
INSERT INTO `dict_message` VALUES ('1005', 'Нужен предмет для удара по боссу', 'Boss strike no item');
INSERT INTO `dict_message` VALUES ('1006', 'Нехватает предметов', 'Not enought items');
INSERT INTO `dict_message` VALUES ('11', 'Ошибка загрузки пользователя', 'User load error');
INSERT INTO `dict_message` VALUES ('2', 'Обьект с этим id не найден в списках словарей', 'Dict obj not found in object list');
INSERT INTO `dict_message` VALUES ('2000', 'Локация успешно пройдена', 'Location win');
INSERT INTO `dict_message` VALUES ('2001', 'Локация не пройдена', 'Location lose');
INSERT INTO `dict_message` VALUES ('2002', 'Бой с боссом в откате', 'Boss fight on cooldown');
INSERT INTO `dict_message` VALUES ('3', 'Пользователь не найден', 'User not found');
INSERT INTO `dict_message` VALUES ('4', 'Обнаружен битый пакет', 'Wrong packet struct');
INSERT INTO `dict_message` VALUES ('5', 'Значение не найдено', 'Value not found');
INSERT INTO `dict_message` VALUES ('5000', 'Packet header not received or corrupted. Connection crushed and closed.', 'Packet header not received or corrupted. Connection crushed and closed.');
INSERT INTO `dict_message` VALUES ('5001', 'Packet with that id can\'t be handled. Connection crushed and closed.', 'Packet with that id can\'t be handled. Connection crushed and closed.');
INSERT INTO `dict_message` VALUES ('5002', 'Expected another size of data of packet with that id thats why pkt can\'t be handled. Connection crushed and closed.', 'Expected another size of data of packet with that id thats why pkt can\'t be handled. Connection crushed and closed.');
INSERT INTO `dict_message` VALUES ('5003', 'Packet expecting structure wrong or corrupted. Connection crushed and closed.', 'Packet expecting structure wrong or corrupted. Connection crushed and closed.');
INSERT INTO `dict_message` VALUES ('5004', 'Packet with that id can\'t be handled by current instance. Connection crushed and closed.', 'Packet with that id can\'t be handled by current instance. Connection crushed and closed.');
INSERT INTO `dict_message` VALUES ('6', 'Обьект не найден', 'Object not found');
INSERT INTO `dict_message` VALUES ('7', 'Защищенный обьект не найден', 'Private object not found');
INSERT INTO `dict_message` VALUES ('8', 'Имя не обнаружено в словаре', 'name not found in dict');
INSERT INTO `dict_message` VALUES ('9', 'Парамент обьекта не найден', 'Object value not found');

-- ----------------------------
-- Table structure for `dict_multilang_interface`
-- ----------------------------
DROP TABLE IF EXISTS `dict_multilang_interface`;
CREATE TABLE `dict_multilang_interface` (
  `object` varchar(64) NOT NULL,
  `ru` varchar(255) NOT NULL,
  `en` varchar(255) NOT NULL,
  `type` set('TEXT','IMAGE','BUTTON') NOT NULL,
  PRIMARY KEY (`object`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_multilang_interface
-- ----------------------------
INSERT INTO `dict_multilang_interface` VALUES ('bosses_access_btn', '/bosses/images/ru/bosses_access_btn_rus.png', '/bosses/images/ru/bosses_access_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_achivements_title', 'Достижения', 'Achievements', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_arrest_btn', '/bosses/images/ru/bosses_arrest_btn_rus.png', '/bosses/images/en/bosses_arrest_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_ask_friend_btn', '/bosses/images/ru/bosses_askfriends_btn_rus.png', '/bosses/images/en/bosses_askfriends_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_atack_btn', '/bosses/images/ru/bosses_atack_btn_rus.png', '/bosses/images/ru/bosses_atack_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_become_best_title', 'Стань лучшим', 'Become The Best', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_best_detective_title', 'Лучший сыщик', 'Best detective', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_buy_btn', '/bosses/images/ru/bosses_buy_btn_rus.png', '/bosses/images/en/bosses_buy_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_difficulty_text', 'Сложность: ', 'difficulty', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_help_btn', '/bosses/images/ru/bosses_help_btn_rus.png', '/bosses/images/ru/bosses_help_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_help_text', 'Текст помощи', 'Help Text', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_help_title', 'Помощь', 'Help', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_last_winner_title', 'Последний победивший', 'Last Winner', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_rewards_title', 'Награды', 'Rewards', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_title_damage_rating', 'Рейтинг урона', 'Damage Rating', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_to_start_text', 'Для начала атаки над боссом вы должны иметь ключи от его дома.', 'To start arresting a villan you must\r have keys from he’s safehouse', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_use_btn', '/bosses/images/ru/bosses_use_btn_rus.png', '/bosses/images/ru/bosses_use_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_use_skills_title', 'Использовать умения', 'Use Skills', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_visit_btn', '/bosses/images/ru/bosses_visit_btn_rus.png', '/bosses/images/ru/bosses_visit_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('bosses_wins_text', 'Побед:', 'Wins:', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('character_selection_choose', 'Выберите своего персонажа', 'Choose your character', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('character_selection_name', 'Детектив', 'Detective', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('character_selection_selected', 'выбрано', 'selected', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('character_selection_take_btn', 'Взять', 'Take', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('collections_my', 'Мои коллекции', 'My Collections', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('collections_my_wishes_title', 'Мои запросы', 'My wishes', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('collections_take_reward_btn', '/collections/images/ru/take_reward_btn_rus.png', '/collections/images/en/take_reward_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('hud_diary_name', '/common/images/ru/diary_btn_rus.png', '/common/images/en/diary_btn_eng.png', 'IMAGE');
INSERT INTO `dict_multilang_interface` VALUES ('hud_play_btn', '/common/images/ru/play_btn_rus.png', '/common/images/en/play_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('hud_tasks_btn', '/common/images/ru/tasks_btn_rus.png', '/common/images/en/tasks_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('hud_tips_btn', '/common/images/ru/tips_btn_rus.png', '/common/images/en/tips_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('icon_characters', 'Персонаж', 'Characters', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_collections', '/common/images/ru/collections_icon_rus.png', '/common/images/en/collections_icon_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('icon_gifts', 'Подарки', 'Gifts', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_inventory', 'Инвентарь', 'Inventory', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_news', 'Новости', 'News', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_sales', 'Продажи', 'Sales', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_shop', 'Магазин', 'Shop', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_talants', 'Таланты', 'Talants', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('icon_villains', '/common/images/ru/villains_icon_rus.png', '/common/images/en/villains_icon_eng.png', '');
INSERT INTO `dict_multilang_interface` VALUES ('locations_again', '/common/images/ru/again_btn_rus.png', '/common/images/en/again_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('locations_close_btn', '/common/images/ru/close_btn_rus.png', '/common/images/en/close_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('locations_completed', '  :  <font color=\"#00FF00\">Выполненно</font>', '  :  <font color=\"#00FF00\">Completed</font>', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_explore_btn', '/common/images/ru/explore_btn_rus.png', '/common/images/en/explore_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('locations_from', 'из', 'from', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_incompleted', '  :  <font color=\"#FF0000\">Не выполненно</font>', '  :  <font color=\"#FF0000\">Not Completed</font>', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_level', 'Уровень:', 'Level:', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_location', 'Локация:', 'Location:', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_locked', 'Заблокировано', 'Locked', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_requirements', 'Требования:', 'Requirements:', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_rewards', 'Награда:', 'Rewards:', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_share_btn', '/common/images/ru/share_btn_rus.png', '/common/images/en/share_btn_eng.png', 'BUTTON');
INSERT INTO `dict_multilang_interface` VALUES ('locations_you_can_find', 'Здесь вы сможете найти', 'Here you can find', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_you_lose', 'Вы проиграли', 'You Lose', 'TEXT');
INSERT INTO `dict_multilang_interface` VALUES ('locations_you_win', 'ВЫ ПОБЕДИЛИ!', 'YOU WIN!', 'TEXT');

-- ----------------------------
-- Table structure for `dict_object`
-- ----------------------------
DROP TABLE IF EXISTS `dict_object`;
CREATE TABLE `dict_object` (
  `id` mediumint(5) unsigned NOT NULL AUTO_INCREMENT,
  `object` varchar(25) NOT NULL,
  `ml_name` varchar(25) NOT NULL,
  `ml_desc` varchar(25) NOT NULL,
  `ml_image` varchar(25) NOT NULL,
  `type` varchar(25) NOT NULL,
  PRIMARY KEY (`id`),
  KEY `desc` (`ml_desc`) USING BTREE,
  KEY `image` (`ml_image`) USING BTREE,
  KEY `type` (`type`) USING BTREE,
  KEY `object` (`object`),
  KEY `ml_name` (`ml_name`),
  CONSTRAINT `dict_object_ibfk_1` FOREIGN KEY (`type`) REFERENCES `dict_object_types` (`type`) ON UPDATE CASCADE,
  CONSTRAINT `dict_object_ibfk_2` FOREIGN KEY (`ml_desc`) REFERENCES `dict_lang` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_object_ibfk_4` FOREIGN KEY (`ml_image`) REFERENCES `dict_lang` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_object_ibfk_5` FOREIGN KEY (`ml_name`) REFERENCES `dict_lang` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=70262 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_object
-- ----------------------------
INSERT INTO `dict_object` VALUES ('1', 'bullets', 'bullets', 'bullets_desc', 'bullets_image', 'BULLETS');
INSERT INTO `dict_object` VALUES ('2', 'exp', 'exp', 'exp_desc', 'exp_image', 'EXP');
INSERT INTO `dict_object` VALUES ('3', 'gold', 'gold', 'gold_desc', 'gold_image', 'GOLD');
INSERT INTO `dict_object` VALUES ('4', 'money', 'money', 'money_desc', 'money_image', 'MONEY');
INSERT INTO `dict_object` VALUES ('5', 'lvl', 'lvl', 'lvl_desc', 'lvl_image', 'LVL');
INSERT INTO `dict_object` VALUES ('6', 'energy', 'energy', 'energy_desc', 'energy_image', 'ENERGY');
INSERT INTO `dict_object` VALUES ('101', 'location_1_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('102', 'location_2_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('103', 'location_3_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('104', 'location_4_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('105', 'location_5_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('106', 'location_6_need_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('2000', 'boss_1_fight_need', 'boss_1_fight_need', 'boss_1_fight_need', 'boss_1_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('2001', 'boss_1', 'boss_1', 'boss_1', 'boss_1_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('2002', 'boss_1_reward_pack', 'boss_1_reward_pack', 'boss_1_reward_pack', 'boss_1_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('3001', 'location_1', 'location_1', 'location_1_desc', 'location_1_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('3002', 'location_2', 'location_2', 'location_2_desc', 'location_2_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('3003', 'location_3', 'location_3', 'location_3_desc', 'location_3_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('3004', 'location_4', 'location_4', 'location_4_desc', 'location_4_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('3005', 'location_5', 'location_5', 'location_5_desc', 'location_5_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('3006', 'location_6', 'location_6', 'location_6_desc', 'location_6_image', 'LOCATION');
INSERT INTO `dict_object` VALUES ('5001', 'coll_monkey1', 'coll_monkey1', 'coll_monkey1_desc', 'coll_monkey1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5002', 'coll_monkey2', 'coll_monkey2', 'coll_monkey2_desc', 'coll_monkey2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5003', 'coll_monkey3', 'coll_monkey3', 'coll_monkey3_desc', 'coll_monkey3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5004', 'coll_monkey4', 'coll_monkey4', 'coll_monkey4_desc', 'coll_monkey4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5005', 'coll_monkey_el', 'coll_monkey_el', 'coll_monkey_el_desc', 'coll_monkey_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5011', 'coll_pipe1', 'coll_pipe1', 'coll_pipe1_desc', 'coll_pipe1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5012', 'coll_pipe2', 'coll_pipe2', 'coll_pipe2_desc', 'coll_pipe2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5013', 'coll_pipe3', 'coll_pipe3', 'coll_pipe3_desc', 'coll_pipe3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5014', 'coll_pipe4', 'coll_pipe4', 'coll_pipe4_desc', 'coll_pipe4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5015', 'coll_pipe_el', 'coll_pipe_el', 'coll_pipe_el_desc', 'coll_pipe_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5021', 'coll_lantern1', 'coll_lantern1', 'coll_lantern1_desc', 'coll_lantern1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5022', 'coll_lantern2', 'coll_lantern2', 'coll_lantern2_desc', 'coll_lantern2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5023', 'coll_lantern3', 'coll_lantern3', 'coll_lantern3_desc', 'coll_lantern3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5024', 'coll_lantern4', 'coll_lantern4', 'coll_lantern4_desc', 'coll_lantern4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5025', 'coll_lantern_el', 'coll_lantern_el', 'coll_lantern_el_desc', 'coll_lantern_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5031', 'coll_key1', 'coll_key1', 'coll_key1_desc', 'coll_key1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5032', 'coll_key2', 'coll_key2', 'coll_key2_desc', 'coll_key2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5033', 'coll_key3', 'coll_key3', 'coll_key3_desc', 'coll_key3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5034', 'coll_key4', 'coll_key4', 'coll_key4_desc', 'coll_key4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5035', 'coll_key_el', 'coll_key_el', 'coll_key_el_desc', 'coll_key_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5041', 'coll_chest1', 'coll_chest1', 'coll_chest1_desc', 'coll_chest1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5042', 'coll_chest2', 'coll_chest2', 'coll_chest2_desc', 'coll_chest2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5043', 'coll_chest3', 'coll_chest3', 'coll_chest3_desc', 'coll_chest3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5044', 'coll_chest4', 'coll_chest4', 'coll_chest4_desc', 'coll_chest4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5045', 'coll_chest_el', 'coll_chest_el', 'coll_chest_el_desc', 'coll_chest_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5051', 'coll_knife1', 'coll_knife1', 'coll_knife1_desc', 'coll_knife1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5052', 'coll_knife2', 'coll_knife2', 'coll_knife2_desc', 'coll_knife2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5053', 'coll_knife3', 'coll_knife3', 'coll_knife3_desc', 'coll_knife3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5054', 'coll_knife4', 'coll_knife4', 'coll_knife4_desc', 'coll_knife4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5055', 'coll_knife_el', 'coll_knife_el', 'coll_knife_el_desc', 'coll_knife_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5061', 'coll_cap1', 'coll_cap1', 'coll_cap1_desc', 'coll_cap1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5062', 'coll_cap2', 'coll_cap2', 'coll_cap2_desc', 'coll_cap2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5063', 'coll_cap3', 'coll_cap3', 'coll_cap3_desc', 'coll_cap3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5064', 'coll_cap4', 'coll_cap4', 'coll_cap4_desc', 'coll_cap4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5065', 'coll_cap_el', 'coll_cap_el', 'coll_cap_el_desc', 'coll_cap_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5071', 'coll_clock1', 'coll_clock1', 'coll_clock1_desc', 'coll_clock1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5072', 'coll_clock2', 'coll_clock2', 'coll_clock2_desc', 'coll_clock2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5073', 'coll_clock3', 'coll_clock3', 'coll_clock3_desc', 'coll_clock3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5074', 'coll_clock4', 'coll_clock4', 'coll_clock4_desc', 'coll_clock4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5075', 'coll_clock_el', 'coll_clock_el', 'coll_clock_el_desc', 'coll_clock_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5081', 'coll_goblet1', 'coll_goblet1', 'coll_goblet1_desc', 'coll_goblet1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5082', 'coll_goblet2', 'coll_goblet2', 'coll_goblet2_desc', 'coll_goblet2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5083', 'coll_goblet3', 'coll_goblet3', 'coll_goblet3_desc', 'coll_goblet3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5084', 'coll_goblet4', 'coll_goblet4', 'coll_goblet4_desc', 'coll_goblet4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5085', 'coll_goblet_el', 'coll_goblet_el', 'coll_goblet_el_desc', 'coll_goblet_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('5091', 'coll_glass1', 'coll_glass1', 'coll_glass1_desc', 'coll_glass1_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5092', 'coll_glass2', 'coll_glass2', 'coll_glass2_desc', 'coll_glass2_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5093', 'coll_glass3', 'coll_glass3', 'coll_glass3_desc', 'coll_glass3_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5094', 'coll_glass4', 'coll_glass4', 'coll_glass4_desc', 'coll_glass4_image', 'COLLECTION_PART');
INSERT INTO `dict_object` VALUES ('5095', 'coll_glass_el', 'coll_glass_el', 'coll_glass_el_desc', 'coll_glass_el_image', 'COLLECTION');
INSERT INTO `dict_object` VALUES ('7001', 'location_1_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('7002', 'location_2_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('7003', 'location_3_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('7004', 'location_4_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('7005', 'location_5_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('7006', 'location_6_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10000', 'location_1_rew_win_pack_1', 'location_1_rew_win', 'location_1_rew_win', 'location_1_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10001', 'location_1_rew_lose_pack', 'location_1_rew_lose', 'location_1_rew_lose', 'location_1_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10002', 'location_2_rew_win_pack_1', 'location_2_rew_win', 'location_2_rew_win', 'location_2_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10003', 'location_2_rew_lose_pack', 'location_2_rew_lose', 'location_2_rew_lose', 'location_2_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10004', 'location_3_rew_lose_pack', 'location_3_rew_lose', 'location_3_rew_lose', 'location_3_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10005', 'location_3_rew_win_pack_1', 'location_3_rew_win', 'location_3_rew_win', 'location_3_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10006', 'location_4_rew_lose_pack', 'location_4_rew_lose', 'location_4_rew_lose', 'location_4_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10007', 'location_4_rew_win_pack_1', 'location_4_rew_win', 'location_4_rew_win', 'location_4_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10008', 'location_5_rew_lose_pack', 'location_5_rew_lose', 'location_5_rew_lose', 'location_5_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10009', 'location_5_rew_win_pack_1', 'location_5_rew_win', 'location_5_rew_win', 'location_5_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10010', 'location_6_rew_lose_pack', 'location_6_rew_lose', 'location_6_rew_lose', 'location_6_rew_lose', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('10012', 'location_6_rew_win_pack_1', 'location_6_rew_win', 'location_6_rew_win', 'location_6_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('20001', 'boss_strike_1', 'boss_strike_1', 'boss_strike_1_desc', 'boss_strike_1_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('20002', 'boss_strike_2', 'boss_strike_2', 'boss_strike_2_desc', 'boss_strike_2_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('20005', 'boss_strike_3', 'boss_strike_3', 'boss_strike_3_desc', 'boss_strike_3_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('20006', 'boss_strike_4', 'boss_strike_4', 'boss_strike_4_desc', 'boss_strike_4_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('20007', 'boss_strike_5', 'boss_strike_5', 'boss_strike_5_desc', 'boss_strike_5_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('70011', 'location_1_wdraw_1', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70015', 'location_3_win_cnt', 'location_3_counter', 'location_3_counter', 'location_3_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70016', 'location_4_win_cnt', 'location_4_counter', 'location_4_counter', 'location_4_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70018', 'location_5_win_cnt', 'location_5_counter', 'location_5_counter', 'location_5_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70019', 'location_6_win_cnt', 'location_6_counter', 'location_6_counter', 'location_6_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70020', 'location_1_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70021', 'location_1_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70023', 'location_1_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70024', 'location_1_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70025', 'location_1_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70027', 'location_2_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70029', 'location_2_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70030', 'location_2_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70031', 'location_2_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70034', 'location_1_win_cnt', 'location_1_counter', 'location_1_counter', 'location_1_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70043', 'location_1_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70045', 'location_1_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70048', 'location_2_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70049', 'location_2_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70050', 'location_2_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70053', 'location_2_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70057', 'location_2_win_cnt', 'location_2_counter', 'location_2_counter', 'location_2_counter', 'ITEM');
INSERT INTO `dict_object` VALUES ('70061', 'location_3_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70062', 'location_3_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70063', 'location_3_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70064', 'location_3_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70067', 'location_3_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70068', 'location_3_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70069', 'location_3_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70071', 'location_3_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70072', 'location_4_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70073', 'location_4_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70074', 'location_4_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70075', 'location_4_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70076', 'location_4_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70077', 'location_4_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70078', 'location_4_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70079', 'location_4_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70080', 'location_5_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70081', 'location_5_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70082', 'location_5_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70083', 'location_5_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70084', 'location_5_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70085', 'location_5_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70086', 'location_5_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70087', 'location_5_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70088', 'location_6_need_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70089', 'location_6_need_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70090', 'location_6_need_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70091', 'location_6_need_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70092', 'location_6_wdraw_2', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70093', 'location_6_wdraw_3', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70094', 'location_6_wdraw_4', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70095', 'location_6_wdraw_5', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70096', 'coll_monkey_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70097', 'coll_cap_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70098', 'coll_chest_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70099', 'coll_clock_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70100', 'coll_glass_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70101', 'coll_goblet_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70102', 'coll_key_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70103', 'coll_knife_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70104', 'coll_lantern_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70105', 'coll_pipe_pack', 'NULL', 'NULL', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70107', 'boss_1_wdraw', 'NULL', 'boss_1_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70108', 'boss_2', 'boss_2', 'boss_2', 'boss_2_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('70110', 'boss_2_fight_need', 'boss_2_fight_need', 'boss_2_fight_need', 'boss_2_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70112', 'boss_2_reward_pack', 'boss_2_reward_pack', 'boss_2_reward_pack', 'boss_2_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70113', 'boss_2_wdraw', 'NULL', 'boss_2_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70114', 'boss_3', 'boss_3', 'boss_3', 'boss_3_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('70115', 'boss_3_fight_need', 'boss_3_fight_need', 'boss_3_fight_need', 'boss_3_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70116', 'boss_3_reward_pack', 'boss_3_reward_pack', 'boss_3_reward_pack', 'boss_3_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70117', 'boss_3_wdraw', 'NULL', 'boss_3_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70118', 'boss_4', 'boss_4', 'boss_4', 'boss_4_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('70119', 'boss_4_fight_need', 'boss_4_fight_need', 'boss_4_fight_need', 'boss_4_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70120', 'boss_4_reward_pack', 'boss_4_reward_pack', 'boss_4_reward_pack', 'boss_4_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70121', 'boss_4_wdraw', 'NULL', 'boss_4_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70122', 'boss_5', 'boss_5', 'boss_5', 'boss_5_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('70123', 'boss_5_fight_need', 'boss_5_fight_need', 'boss_5_fight_need', 'boss_5_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70125', 'boss_5_reward_pack', 'boss_5_reward_pack', 'boss_5_reward_pack', 'boss_5_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70126', 'boss_5_wdraw', 'NULL', 'boss_5_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70127', 'boss_6', 'boss_6', 'boss_6', 'boss_6_image', 'BOSS');
INSERT INTO `dict_object` VALUES ('70128', 'boss_6_fight_need', 'boss_6_fight_need', 'boss_6_fight_need', 'boss_6_fight_need', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70130', 'boss_6_reward_pack', 'boss_6_reward_pack', 'boss_6_reward_pack', 'boss_6_reward_pack', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70131', 'boss_6_wdraw', 'NULL', 'boss_6_wdraw', 'NULL', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70132', 'boss_1_key', 'boss_1_key', 'boss_1_key', 'boss_1_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70133', 'boss_2_key', 'boss_2_key', 'boss_2_key', 'boss_2_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70134', 'boss_3_key', 'boss_3_key', 'boss_3_key', 'boss_3_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70135', 'boss_4_key', 'boss_4_key', 'boss_4_key', 'boss_4_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70136', 'boss_5_key', 'boss_5_key', 'boss_5_key', 'boss_5_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70137', 'boss_6_key', 'boss_6_key', 'boss_6_key', 'boss_6_key_image', 'ITEM');
INSERT INTO `dict_object` VALUES ('70138', 'boss_strike_6', 'boss_strike_6', 'boss_strike_6_desc', 'boss_strike_6_img', 'BOSS_STRIKE');
INSERT INTO `dict_object` VALUES ('70141', 'location_1_rew_win_pack_2', 'location_1_rew_win', 'location_1_rew_win', 'location_1_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70142', 'location_1_rew_win_pack_3', 'location_1_rew_win', 'location_1_rew_win', 'location_1_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70143', 'location_1_rew_win_pack_4', 'location_1_rew_win', 'location_1_rew_win', 'location_1_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70144', 'location_1_rew_win_pack_5', 'location_1_rew_win', 'location_1_rew_win', 'location_1_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70145', 'location_2_rew_win_pack_2', 'location_2_rew_win', 'location_2_rew_win', 'location_2_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70146', 'location_2_rew_win_pack_3', 'location_2_rew_win', 'location_2_rew_win', 'location_2_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70147', 'location_2_rew_win_pack_4', 'location_2_rew_win', 'location_2_rew_win', 'location_2_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70148', 'location_2_rew_win_pack_5', 'location_2_rew_win', 'location_2_rew_win', 'location_2_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70149', 'location_3_rew_win_pack_2', 'location_3_rew_win', 'location_3_rew_win', 'location_3_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70150', 'location_3_rew_win_pack_3', 'location_3_rew_win', 'location_3_rew_win', 'location_3_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70151', 'location_3_rew_win_pack_4', 'location_3_rew_win', 'location_3_rew_win', 'location_3_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70152', 'location_3_rew_win_pack_5', 'location_3_rew_win', 'location_3_rew_win', 'location_3_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70153', 'location_4_rew_win_pack_2', 'location_4_rew_win', 'location_4_rew_win', 'location_4_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70154', 'location_4_rew_win_pack_3', 'location_4_rew_win', 'location_4_rew_win', 'location_4_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70155', 'location_4_rew_win_pack_4', 'location_4_rew_win', 'location_4_rew_win', 'location_4_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70156', 'location_4_rew_win_pack_5', 'location_4_rew_win', 'location_4_rew_win', 'location_4_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70157', 'location_5_rew_win_pack_2', 'location_5_rew_win', 'location_5_rew_win', 'location_5_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70158', 'location_5_rew_win_pack_3', 'location_5_rew_win', 'location_5_rew_win', 'location_5_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70159', 'location_5_rew_win_pack_4', 'location_5_rew_win', 'location_5_rew_win', 'location_5_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70160', 'location_5_rew_win_pack_5', 'location_5_rew_win', 'location_5_rew_win', 'location_5_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70161', 'location_6_rew_win_pack_2', 'location_6_rew_win', 'location_6_rew_win', 'location_6_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70162', 'location_6_rew_win_pack_3', 'location_6_rew_win', 'location_6_rew_win', 'location_6_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70163', 'location_6_rew_win_pack_4', 'location_6_rew_win', 'location_6_rew_win', 'location_6_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70164', 'location_6_rew_win_pack_5', 'location_6_rew_win', 'location_6_rew_win', 'location_6_rew_win', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70191', 'location_1_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70192', 'location_2_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70193', 'location_3_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70194', 'location_4_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70195', 'location_5_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70196', 'location_6_level_pack_1', 'location_level_1', 'location_level_1', 'location_level_1', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70197', 'location_1_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70198', 'location_2_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70199', 'location_3_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70200', 'location_4_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70201', 'location_5_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70202', 'location_6_level_pack_2', 'location_level_2', 'location_level_2', 'location_level_2', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70203', 'location_1_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70204', 'location_2_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70205', 'location_3_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70206', 'location_4_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70207', 'location_5_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70208', 'location_6_level_pack_3', 'location_level_3', 'location_level_3', 'location_level_3', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70209', 'location_1_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70210', 'location_2_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70211', 'location_3_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70212', 'location_4_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70213', 'location_5_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70214', 'location_6_level_pack_4', 'location_level_4', 'location_level_4', 'location_level_4', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70215', 'location_1_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70216', 'location_2_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70217', 'location_3_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70218', 'location_4_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70219', 'location_5_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70220', 'location_6_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70221', 'location_6_level_pack_5', 'location_level_5', 'location_level_5', 'location_level_5', 'ITEM_PACK');
INSERT INTO `dict_object` VALUES ('70249', 'location_mode_dark', 'location_mode_dark', 'location_mode_dark', 'location_mode_dark', 'ITEM');
INSERT INTO `dict_object` VALUES ('70250', 'location_mode_ghost', 'location_mode_ghost', 'location_mode_ghost', 'location_mode_ghost', 'ITEM');
INSERT INTO `dict_object` VALUES ('70251', 'location_mode_random', 'location_mode_random', 'location_mode_random', 'location_mode_random', 'ITEM');
INSERT INTO `dict_object` VALUES ('70252', 'location_mode_position', 'location_mode_position', 'location_mode_position', 'location_mode_position', 'ITEM');
INSERT INTO `dict_object` VALUES ('70253', 'location_mode_shadow', 'location_mode_shadow', 'location_mode_shadow', 'location_mode_shadow', 'ITEM');
INSERT INTO `dict_object` VALUES ('70254', 'location_mode_flip', 'location_mode_flip', 'location_mode_flip', 'location_mode_flip', 'ITEM');
INSERT INTO `dict_object` VALUES ('70255', 'location_mode_oneword', 'location_mode_oneword', 'location_mode_oneword', 'location_mode_oneword', 'ITEM');
INSERT INTO `dict_object` VALUES ('70256', 'location_mode_night', 'location_mode_night', 'location_mode_night', 'location_mode_night', 'ITEM');
INSERT INTO `dict_object` VALUES ('70257', 'location_mode_timestep', 'location_mode_timestep', 'location_mode_timestep', 'location_mode_timestep', 'ITEM');
INSERT INTO `dict_object` VALUES ('70258', 'location_mode_shuffletext', 'location_mode_shuffletext', 'location_mode_shuffletext', 'location_mode_shuffletext', 'ITEM');
INSERT INTO `dict_object` VALUES ('70259', 'location_mode_drag', 'location_mode_drag', 'location_mode_drag', 'location_mode_drag', 'ITEM');
INSERT INTO `dict_object` VALUES ('70260', 'location_mode_smog', 'location_mode_smog', 'location_mode_smog', 'location_mode_smog', 'ITEM');
INSERT INTO `dict_object` VALUES ('70261', 'location_mode_flash', 'location_mode_flash', 'location_mode_flash', 'location_mode_flash', 'ITEM');

-- ----------------------------
-- Table structure for `dict_object_types`
-- ----------------------------
DROP TABLE IF EXISTS `dict_object_types`;
CREATE TABLE `dict_object_types` (
  `type` varchar(25) NOT NULL,
  `table` varchar(25) NOT NULL,
  PRIMARY KEY (`type`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_object_types
-- ----------------------------
INSERT INTO `dict_object_types` VALUES ('BOSS', 'dict_boss');
INSERT INTO `dict_object_types` VALUES ('BOSS_STRIKE', 'dict_boss_strike');
INSERT INTO `dict_object_types` VALUES ('BULLETS', 'global');
INSERT INTO `dict_object_types` VALUES ('COLLECTION', 'global');
INSERT INTO `dict_object_types` VALUES ('COLLECTION_PART', 'global');
INSERT INTO `dict_object_types` VALUES ('ENERGY', 'global');
INSERT INTO `dict_object_types` VALUES ('EXP', 'global');
INSERT INTO `dict_object_types` VALUES ('GOLD', 'global');
INSERT INTO `dict_object_types` VALUES ('ITEM', 'global');
INSERT INTO `dict_object_types` VALUES ('ITEM_PACK', 'global');
INSERT INTO `dict_object_types` VALUES ('LOCATION', 'global');
INSERT INTO `dict_object_types` VALUES ('LVL', 'global');
INSERT INTO `dict_object_types` VALUES ('MONEY', 'global');

-- ----------------------------
-- Table structure for `dict_pack`
-- ----------------------------
DROP TABLE IF EXISTS `dict_pack`;
CREATE TABLE `dict_pack` (
  `object` varchar(25) NOT NULL,
  `in_pack_obj` varchar(25) NOT NULL,
  `count` smallint(5) unsigned NOT NULL,
  `record_id` smallint(5) unsigned NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`record_id`),
  KEY `in_pack_item` (`in_pack_obj`) USING BTREE,
  KEY `pack` (`object`) USING BTREE,
  KEY `object` (`object`,`in_pack_obj`),
  CONSTRAINT `dict_pack_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `in_pack_obj_fk` FOREIGN KEY (`in_pack_obj`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=9318 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_pack
-- ----------------------------
INSERT INTO `dict_pack` VALUES ('location_1_rew_lose_pack', 'money', '1', '0');
INSERT INTO `dict_pack` VALUES ('boss_1_reward_pack', 'money', '50', '1');
INSERT INTO `dict_pack` VALUES ('boss_1_reward_pack', 'exp', '100', '2');
INSERT INTO `dict_pack` VALUES ('boss_1_fight_need', 'location_1_win_cnt', '10', '4');
INSERT INTO `dict_pack` VALUES ('location_1_rew_lose_pack', 'exp', '12', '6001');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'exp', '25', '6002');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'money', '30', '6003');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'coll_monkey4', '1', '6004');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'coll_monkey2', '1', '6005');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'coll_monkey1', '1', '6006');
INSERT INTO `dict_pack` VALUES ('location_2_rew_lose_pack', 'money', '2', '6007');
INSERT INTO `dict_pack` VALUES ('location_2_rew_lose_pack', 'exp', '15', '6008');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_1', 'exp', '50', '6009');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_1', 'money', '60', '6010');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_1', 'coll_lantern2', '1', '6011');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_1', 'coll_lantern3', '1', '6012');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_1', 'coll_key1', '1', '6013');
INSERT INTO `dict_pack` VALUES ('location_3_rew_lose_pack', 'money', '3', '6014');
INSERT INTO `dict_pack` VALUES ('location_3_rew_lose_pack', 'exp', '16', '6015');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_1', 'exp', '100', '6016');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_1', 'money', '130', '6022');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_1', 'coll_chest2', '1', '6024');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_1', 'coll_pipe3', '1', '6025');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_1', 'coll_key3', '1', '6027');
INSERT INTO `dict_pack` VALUES ('location_4_rew_lose_pack', 'money', '4', '6028');
INSERT INTO `dict_pack` VALUES ('location_4_rew_lose_pack', 'exp', '17', '6029');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_1', 'exp', '150', '6030');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_1', 'money', '140', '6031');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_1', 'coll_key2', '1', '6032');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_1', 'coll_key4', '1', '6033');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_1', 'coll_glass1', '1', '6034');
INSERT INTO `dict_pack` VALUES ('location_5_rew_lose_pack', 'money', '5', '6035');
INSERT INTO `dict_pack` VALUES ('location_5_rew_lose_pack', 'exp', '18', '6036');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_1', 'exp', '200', '6037');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_1', 'money', '150', '6038');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_1', 'coll_chest4', '1', '6039');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_1', 'coll_cap2', '1', '6040');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_1', 'coll_pipe4', '1', '6041');
INSERT INTO `dict_pack` VALUES ('location_6_rew_lose_pack', 'money', '6', '6043');
INSERT INTO `dict_pack` VALUES ('location_6_rew_lose_pack', 'exp', '19', '6044');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_1', 'money', '200', '6045');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_1', 'exp', '250', '6046');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_1', 'coll_clock1', '1', '6047');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_1', 'coll_clock3', '1', '6048');
INSERT INTO `dict_pack` VALUES ('location_1_wdraw_3', 'energy', '9', '8001');
INSERT INTO `dict_pack` VALUES ('location_2_wdraw_1', 'energy', '8', '8002');
INSERT INTO `dict_pack` VALUES ('location_3_wdraw_2', 'energy', '14', '8003');
INSERT INTO `dict_pack` VALUES ('location_4_wdraw_1', 'energy', '10', '8004');
INSERT INTO `dict_pack` VALUES ('location_5_wdraw_1', 'energy', '11', '8005');
INSERT INTO `dict_pack` VALUES ('location_6_wdraw_1', 'energy', '12', '8006');
INSERT INTO `dict_pack` VALUES ('location_1_wdraw_1', 'energy', '5', '8007');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_1', 'location_1_win_cnt', '1', '8011');
INSERT INTO `dict_pack` VALUES ('location_1_wdraw_2', 'energy', '7', '8017');
INSERT INTO `dict_pack` VALUES ('location_1_wdraw_4', 'energy', '11', '8023');
INSERT INTO `dict_pack` VALUES ('location_1_wdraw_5', 'energy', '15', '8024');
INSERT INTO `dict_pack` VALUES ('location_2_wdraw_2', 'energy', '12', '8034');
INSERT INTO `dict_pack` VALUES ('location_2_wdraw_3', 'energy', '16', '8035');
INSERT INTO `dict_pack` VALUES ('location_2_wdraw_4', 'energy', '20', '8036');
INSERT INTO `dict_pack` VALUES ('location_2_wdraw_5', 'energy', '24', '8037');
INSERT INTO `dict_pack` VALUES ('location_3_wdraw_1', 'energy', '9', '8076');
INSERT INTO `dict_pack` VALUES ('location_3_wdraw_3', 'energy', '19', '8077');
INSERT INTO `dict_pack` VALUES ('location_3_wdraw_4', 'energy', '24', '8078');
INSERT INTO `dict_pack` VALUES ('location_3_wdraw_5', 'energy', '29', '8079');
INSERT INTO `dict_pack` VALUES ('location_4_wdraw_2', 'energy', '16', '8080');
INSERT INTO `dict_pack` VALUES ('location_4_wdraw_3', 'energy', '22', '8081');
INSERT INTO `dict_pack` VALUES ('location_4_wdraw_4', 'energy', '28', '8082');
INSERT INTO `dict_pack` VALUES ('location_4_wdraw_5', 'energy', '34', '8083');
INSERT INTO `dict_pack` VALUES ('location_5_wdraw_2', 'energy', '18', '8084');
INSERT INTO `dict_pack` VALUES ('location_5_wdraw_3', 'energy', '25', '8085');
INSERT INTO `dict_pack` VALUES ('location_5_wdraw_4', 'energy', '32', '8086');
INSERT INTO `dict_pack` VALUES ('location_5_wdraw_5', 'energy', '39', '8087');
INSERT INTO `dict_pack` VALUES ('location_6_wdraw_2', 'energy', '20', '8088');
INSERT INTO `dict_pack` VALUES ('location_6_wdraw_3', 'energy', '28', '8089');
INSERT INTO `dict_pack` VALUES ('location_6_wdraw_4', 'energy', '36', '8090');
INSERT INTO `dict_pack` VALUES ('location_6_wdraw_5', 'energy', '44', '8091');
INSERT INTO `dict_pack` VALUES ('location_1_need_1', 'lvl', '1', '9001');
INSERT INTO `dict_pack` VALUES ('location_1_need_2', 'lvl', '2', '9002');
INSERT INTO `dict_pack` VALUES ('location_1_need_2', 'location_1_win_cnt', '5', '9003');
INSERT INTO `dict_pack` VALUES ('location_1_need_3', 'lvl', '3', '9004');
INSERT INTO `dict_pack` VALUES ('location_1_need_3', 'location_1_win_cnt', '10', '9005');
INSERT INTO `dict_pack` VALUES ('location_1_need_4', 'lvl', '4', '9006');
INSERT INTO `dict_pack` VALUES ('location_1_need_4', 'location_1_win_cnt', '25', '9007');
INSERT INTO `dict_pack` VALUES ('location_1_need_5', 'lvl', '5', '9008');
INSERT INTO `dict_pack` VALUES ('location_1_need_5', 'location_1_win_cnt', '75', '9009');
INSERT INTO `dict_pack` VALUES ('location_2_need_1', 'lvl', '1', '9021');
INSERT INTO `dict_pack` VALUES ('location_2_need_1', 'location_1_win_cnt', '10', '9022');
INSERT INTO `dict_pack` VALUES ('location_2_need_2', 'lvl', '2', '9023');
INSERT INTO `dict_pack` VALUES ('location_2_need_2', 'location_2_win_cnt', '5', '9024');
INSERT INTO `dict_pack` VALUES ('location_2_need_3', 'lvl', '3', '9025');
INSERT INTO `dict_pack` VALUES ('location_2_need_3', 'location_2_win_cnt', '10', '9026');
INSERT INTO `dict_pack` VALUES ('location_2_need_4', 'lvl', '4', '9027');
INSERT INTO `dict_pack` VALUES ('location_2_need_4', 'location_2_win_cnt', '25', '9028');
INSERT INTO `dict_pack` VALUES ('location_2_need_5', 'location_2_win_cnt', '75', '9029');
INSERT INTO `dict_pack` VALUES ('location_2_need_5', 'lvl', '5', '9030');
INSERT INTO `dict_pack` VALUES ('location_3_need_3', 'lvl', '3', '9036');
INSERT INTO `dict_pack` VALUES ('location_3_need_3', 'location_3_win_cnt', '10', '9037');
INSERT INTO `dict_pack` VALUES ('location_3_need_1', 'money', '50', '9041');
INSERT INTO `dict_pack` VALUES ('location_3_need_1', 'lvl', '1', '9042');
INSERT INTO `dict_pack` VALUES ('location_3_need_1', 'energy', '7', '9043');
INSERT INTO `dict_pack` VALUES ('location_3_need_1', 'location_2_win_cnt', '20', '9044');
INSERT INTO `dict_pack` VALUES ('location_3_need_2', 'location_3_win_cnt', '5', '9045');
INSERT INTO `dict_pack` VALUES ('location_3_need_2', 'lvl', '2', '9046');
INSERT INTO `dict_pack` VALUES ('location_3_need_4', 'lvl', '4', '9047');
INSERT INTO `dict_pack` VALUES ('location_3_need_4', 'location_3_win_cnt', '25', '9048');
INSERT INTO `dict_pack` VALUES ('location_3_need_5', 'location_3_win_cnt', '75', '9049');
INSERT INTO `dict_pack` VALUES ('location_3_need_5', 'lvl', '5', '9050');
INSERT INTO `dict_pack` VALUES ('location_4_need_1', 'money', '60', '9061');
INSERT INTO `dict_pack` VALUES ('location_4_need_1', 'energy', '8', '9062');
INSERT INTO `dict_pack` VALUES ('location_4_need_1', 'location_3_win_cnt', '30', '9063');
INSERT INTO `dict_pack` VALUES ('location_4_need_1', 'lvl', '1', '9064');
INSERT INTO `dict_pack` VALUES ('location_4_need_2', 'location_4_win_cnt', '5', '9065');
INSERT INTO `dict_pack` VALUES ('location_4_need_2', 'lvl', '2', '9066');
INSERT INTO `dict_pack` VALUES ('location_4_need_3', 'lvl', '3', '9067');
INSERT INTO `dict_pack` VALUES ('location_4_need_3', 'location_4_win_cnt', '10', '9068');
INSERT INTO `dict_pack` VALUES ('location_4_need_4', 'location_4_win_cnt', '25', '9069');
INSERT INTO `dict_pack` VALUES ('location_4_need_4', 'lvl', '4', '9070');
INSERT INTO `dict_pack` VALUES ('location_4_need_5', 'lvl', '5', '9071');
INSERT INTO `dict_pack` VALUES ('location_4_need_5', 'location_4_win_cnt', '75', '9072');
INSERT INTO `dict_pack` VALUES ('location_5_need_1', 'energy', '9', '9081');
INSERT INTO `dict_pack` VALUES ('location_5_need_1', 'lvl', '1', '9082');
INSERT INTO `dict_pack` VALUES ('location_5_need_1', 'location_4_win_cnt', '40', '9083');
INSERT INTO `dict_pack` VALUES ('location_5_need_1', 'money', '70', '9084');
INSERT INTO `dict_pack` VALUES ('location_5_need_2', 'location_5_win_cnt', '2', '9085');
INSERT INTO `dict_pack` VALUES ('location_5_need_2', 'lvl', '2', '9086');
INSERT INTO `dict_pack` VALUES ('location_5_need_3', 'lvl', '3', '9087');
INSERT INTO `dict_pack` VALUES ('location_5_need_3', 'location_5_win_cnt', '10', '9088');
INSERT INTO `dict_pack` VALUES ('location_5_need_4', 'lvl', '4', '9090');
INSERT INTO `dict_pack` VALUES ('location_5_need_4', 'location_5_win_cnt', '25', '9091');
INSERT INTO `dict_pack` VALUES ('location_5_need_5', 'location_5_win_cnt', '75', '9092');
INSERT INTO `dict_pack` VALUES ('location_5_need_5', 'lvl', '5', '9093');
INSERT INTO `dict_pack` VALUES ('location_6_need_1', 'location_5_win_cnt', '50', '9101');
INSERT INTO `dict_pack` VALUES ('location_6_need_1', 'money', '80', '9102');
INSERT INTO `dict_pack` VALUES ('location_6_need_1', 'lvl', '1', '9103');
INSERT INTO `dict_pack` VALUES ('location_6_need_1', 'energy', '12', '9104');
INSERT INTO `dict_pack` VALUES ('location_6_need_2', 'location_6_win_cnt', '5', '9105');
INSERT INTO `dict_pack` VALUES ('location_6_need_2', 'lvl', '2', '9106');
INSERT INTO `dict_pack` VALUES ('location_6_need_3', 'location_6_win_cnt', '10', '9107');
INSERT INTO `dict_pack` VALUES ('location_6_need_3', 'lvl', '3', '9108');
INSERT INTO `dict_pack` VALUES ('location_6_need_4', 'lvl', '4', '9109');
INSERT INTO `dict_pack` VALUES ('location_6_need_4', 'location_6_win_cnt', '25', '9110');
INSERT INTO `dict_pack` VALUES ('location_6_need_5', 'location_6_win_cnt', '75', '9111');
INSERT INTO `dict_pack` VALUES ('location_6_need_5', 'lvl', '5', '9112');
INSERT INTO `dict_pack` VALUES ('coll_monkey_pack', 'coll_monkey1', '1', '9114');
INSERT INTO `dict_pack` VALUES ('coll_monkey_pack', 'coll_monkey2', '1', '9115');
INSERT INTO `dict_pack` VALUES ('coll_monkey_pack', 'coll_monkey3', '1', '9116');
INSERT INTO `dict_pack` VALUES ('coll_monkey_pack', 'coll_monkey4', '1', '9117');
INSERT INTO `dict_pack` VALUES ('coll_cap_pack', 'coll_cap1', '1', '9118');
INSERT INTO `dict_pack` VALUES ('coll_cap_pack', 'coll_cap2', '1', '9119');
INSERT INTO `dict_pack` VALUES ('coll_cap_pack', 'coll_cap3', '1', '9120');
INSERT INTO `dict_pack` VALUES ('coll_cap_pack', 'coll_cap4', '1', '9121');
INSERT INTO `dict_pack` VALUES ('coll_chest_pack', 'coll_chest1', '1', '9122');
INSERT INTO `dict_pack` VALUES ('coll_chest_pack', 'coll_chest2', '1', '9123');
INSERT INTO `dict_pack` VALUES ('coll_chest_pack', 'coll_chest3', '1', '9124');
INSERT INTO `dict_pack` VALUES ('coll_chest_pack', 'coll_chest4', '1', '9125');
INSERT INTO `dict_pack` VALUES ('coll_clock_pack', 'coll_clock1', '1', '9127');
INSERT INTO `dict_pack` VALUES ('coll_clock_pack', 'coll_clock2', '1', '9128');
INSERT INTO `dict_pack` VALUES ('coll_clock_pack', 'coll_clock3', '1', '9129');
INSERT INTO `dict_pack` VALUES ('coll_clock_pack', 'coll_clock4', '1', '9130');
INSERT INTO `dict_pack` VALUES ('coll_glass_pack', 'coll_glass1', '1', '9131');
INSERT INTO `dict_pack` VALUES ('coll_glass_pack', 'coll_glass2', '1', '9132');
INSERT INTO `dict_pack` VALUES ('coll_glass_pack', 'coll_glass3', '1', '9133');
INSERT INTO `dict_pack` VALUES ('coll_glass_pack', 'coll_glass4', '1', '9134');
INSERT INTO `dict_pack` VALUES ('coll_goblet_pack', 'coll_goblet1', '1', '9135');
INSERT INTO `dict_pack` VALUES ('coll_goblet_pack', 'coll_goblet2', '1', '9136');
INSERT INTO `dict_pack` VALUES ('coll_goblet_pack', 'coll_goblet3', '1', '9137');
INSERT INTO `dict_pack` VALUES ('coll_goblet_pack', 'coll_goblet4', '1', '9138');
INSERT INTO `dict_pack` VALUES ('coll_key_pack', 'coll_key1', '1', '9139');
INSERT INTO `dict_pack` VALUES ('coll_key_pack', 'coll_key2', '1', '9141');
INSERT INTO `dict_pack` VALUES ('coll_key_pack', 'coll_key3', '1', '9142');
INSERT INTO `dict_pack` VALUES ('coll_key_pack', 'coll_key4', '1', '9143');
INSERT INTO `dict_pack` VALUES ('coll_knife_pack', 'coll_knife1', '1', '9144');
INSERT INTO `dict_pack` VALUES ('coll_knife_pack', 'coll_knife2', '1', '9145');
INSERT INTO `dict_pack` VALUES ('coll_knife_pack', 'coll_knife3', '1', '9146');
INSERT INTO `dict_pack` VALUES ('coll_knife_pack', 'coll_knife4', '1', '9147');
INSERT INTO `dict_pack` VALUES ('coll_lantern_pack', 'coll_lantern1', '1', '9148');
INSERT INTO `dict_pack` VALUES ('coll_lantern_pack', 'coll_lantern2', '1', '9149');
INSERT INTO `dict_pack` VALUES ('coll_lantern_pack', 'coll_lantern3', '1', '9150');
INSERT INTO `dict_pack` VALUES ('coll_lantern_pack', 'coll_lantern4', '1', '9151');
INSERT INTO `dict_pack` VALUES ('coll_pipe_pack', 'coll_pipe1', '1', '9152');
INSERT INTO `dict_pack` VALUES ('coll_pipe_pack', 'coll_pipe2', '1', '9153');
INSERT INTO `dict_pack` VALUES ('coll_pipe_pack', 'coll_pipe3', '1', '9154');
INSERT INTO `dict_pack` VALUES ('coll_pipe_pack', 'coll_pipe4', '1', '9155');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_1', 'coll_goblet2', '1', '9156');
INSERT INTO `dict_pack` VALUES ('boss_1_wdraw', 'energy', '5', '9157');
INSERT INTO `dict_pack` VALUES ('boss_2_reward_pack', 'money', '70', '9159');
INSERT INTO `dict_pack` VALUES ('boss_2_fight_need', 'location_2_win_cnt', '10', '9160');
INSERT INTO `dict_pack` VALUES ('boss_2_reward_pack', 'exp', '110', '9161');
INSERT INTO `dict_pack` VALUES ('boss_2_wdraw', 'energy', '10', '9162');
INSERT INTO `dict_pack` VALUES ('boss_3_fight_need', 'location_3_win_cnt', '10', '9163');
INSERT INTO `dict_pack` VALUES ('boss_3_reward_pack', 'exp', '120', '9167');
INSERT INTO `dict_pack` VALUES ('boss_3_reward_pack', 'money', '90', '9168');
INSERT INTO `dict_pack` VALUES ('boss_3_wdraw', 'energy', '15', '9169');
INSERT INTO `dict_pack` VALUES ('boss_4_fight_need', 'location_4_win_cnt', '10', '9170');
INSERT INTO `dict_pack` VALUES ('boss_4_reward_pack', 'money', '110', '9171');
INSERT INTO `dict_pack` VALUES ('boss_4_reward_pack', 'exp', '130', '9172');
INSERT INTO `dict_pack` VALUES ('boss_4_wdraw', 'energy', '20', '9173');
INSERT INTO `dict_pack` VALUES ('boss_5_fight_need', 'location_5_win_cnt', '10', '9174');
INSERT INTO `dict_pack` VALUES ('boss_5_reward_pack', 'exp', '140', '9175');
INSERT INTO `dict_pack` VALUES ('boss_5_reward_pack', 'money', '120', '9176');
INSERT INTO `dict_pack` VALUES ('boss_5_wdraw', 'energy', '25', '9177');
INSERT INTO `dict_pack` VALUES ('boss_6_fight_need', 'location_6_win_cnt', '10', '9178');
INSERT INTO `dict_pack` VALUES ('boss_6_reward_pack', 'exp', '150', '9180');
INSERT INTO `dict_pack` VALUES ('boss_6_reward_pack', 'money', '130', '9181');
INSERT INTO `dict_pack` VALUES ('boss_6_wdraw', 'energy', '30', '9182');
INSERT INTO `dict_pack` VALUES ('boss_2_fight_need', 'boss_1_key', '3', '9184');
INSERT INTO `dict_pack` VALUES ('boss_3_fight_need', 'boss_2_key', '6', '9185');
INSERT INTO `dict_pack` VALUES ('boss_4_fight_need', 'boss_3_key', '12', '9186');
INSERT INTO `dict_pack` VALUES ('boss_5_fight_need', 'boss_4_key', '24', '9187');
INSERT INTO `dict_pack` VALUES ('boss_6_fight_need', 'boss_5_key', '48', '9188');
INSERT INTO `dict_pack` VALUES ('boss_1_reward_pack', 'boss_1_key', '1', '9189');
INSERT INTO `dict_pack` VALUES ('boss_2_reward_pack', 'boss_2_key', '1', '9190');
INSERT INTO `dict_pack` VALUES ('boss_3_reward_pack', 'boss_3_key', '1', '9191');
INSERT INTO `dict_pack` VALUES ('boss_4_reward_pack', 'boss_4_key', '1', '9192');
INSERT INTO `dict_pack` VALUES ('boss_5_reward_pack', 'boss_5_key', '1', '9193');
INSERT INTO `dict_pack` VALUES ('boss_6_reward_pack', 'boss_6_key', '1', '9194');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_2', 'location_1_win_cnt', '1', '9195');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_3', 'location_1_win_cnt', '1', '9196');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_4', 'location_1_win_cnt', '1', '9197');
INSERT INTO `dict_pack` VALUES ('location_1_rew_win_pack_5', 'location_1_win_cnt', '1', '9198');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_2', 'location_2_win_cnt', '1', '9199');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_3', 'location_2_win_cnt', '1', '9200');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_4', 'location_2_win_cnt', '1', '9201');
INSERT INTO `dict_pack` VALUES ('location_2_rew_win_pack_5', 'location_2_win_cnt', '1', '9202');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_2', 'location_3_win_cnt', '1', '9203');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_3', 'location_3_win_cnt', '1', '9204');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_4', 'location_3_win_cnt', '1', '9205');
INSERT INTO `dict_pack` VALUES ('location_3_rew_win_pack_5', 'location_3_win_cnt', '1', '9206');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_2', 'location_4_win_cnt', '1', '9207');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_3', 'location_4_win_cnt', '1', '9208');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_4', 'location_4_win_cnt', '1', '9209');
INSERT INTO `dict_pack` VALUES ('location_4_rew_win_pack_5', 'location_4_win_cnt', '1', '9210');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_2', 'location_5_win_cnt', '1', '9211');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_3', 'location_5_win_cnt', '1', '9212');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_4', 'location_5_win_cnt', '1', '9213');
INSERT INTO `dict_pack` VALUES ('location_5_rew_win_pack_5', 'location_5_win_cnt', '1', '9214');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_2', 'location_6_win_cnt', '1', '9215');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_3', 'location_6_win_cnt', '1', '9216');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_4', 'location_6_win_cnt', '1', '9217');
INSERT INTO `dict_pack` VALUES ('location_6_rew_win_pack_5', 'location_6_win_cnt', '1', '9218');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_random', '5', '9253');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_position', '1', '9254');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_flip', '1', '9255');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_shadow', '1', '9256');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_ghost', '1', '9257');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_dark', '1', '9258');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_shuffletext', '1', '9259');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_night', '1', '9260');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_oneword', '1', '9261');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_timestep', '1', '9262');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_drag', '1', '9263');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_smog', '1', '9264');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_1', 'location_mode_flash', '1', '9265');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_random', '10', '9266');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_flip', '1', '9267');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_shadow', '1', '9268');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_ghost', '1', '9269');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_dark', '1', '9270');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_shuffletext', '1', '9271');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_night', '1', '9272');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_oneword', '1', '9273');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_timestep', '1', '9274');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_drag', '1', '9275');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_smog', '1', '9276');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_2', 'location_mode_flash', '1', '9277');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_ghost', '1', '9278');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_dark', '1', '9279');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_shuffletext', '1', '9280');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_night', '1', '9281');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_oneword', '1', '9282');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_timestep', '1', '9283');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_drag', '1', '9284');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_smog', '1', '9285');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_3', 'location_mode_flash', '1', '9286');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_4', 'location_mode_oneword', '1', '9287');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_4', 'location_mode_timestep', '1', '9288');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_4', 'location_mode_drag', '1', '9289');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_4', 'location_mode_smog', '1', '9290');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_4', 'location_mode_flash', '1', '9291');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_5', 'location_mode_random', '15', '9292');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_ghost', '1', '9294');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_dark', '1', '9295');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_shuffletext', '1', '9296');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_night', '1', '9297');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_oneword', '1', '9298');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_timestep', '1', '9299');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_drag', '1', '9300');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_smog', '1', '9301');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_1', 'location_mode_flash', '1', '9302');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_ghost', '1', '9303');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_dark', '1', '9304');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_shuffletext', '1', '9305');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_night', '1', '9306');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_oneword', '1', '9307');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_timestep', '1', '9308');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_drag', '1', '9309');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_smog', '1', '9310');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_2', 'location_mode_flash', '1', '9311');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_3', 'location_mode_oneword', '1', '9312');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_3', 'location_mode_timestep', '1', '9313');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_3', 'location_mode_drag', '1', '9314');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_3', 'location_mode_smog', '1', '9315');
INSERT INTO `dict_pack` VALUES ('location_2_level_pack_3', 'location_mode_flash', '1', '9316');
INSERT INTO `dict_pack` VALUES ('location_1_level_pack_5', 'location_mode_random', '15', '9317');

-- ----------------------------
-- Table structure for `dict_swf_object`
-- ----------------------------
DROP TABLE IF EXISTS `dict_swf_object`;
CREATE TABLE `dict_swf_object` (
  `object` varchar(25) NOT NULL,
  `ml_swf` varchar(255) NOT NULL,
  PRIMARY KEY (`object`),
  KEY `ml_swf` (`ml_swf`),
  CONSTRAINT `dict_swf_object_ibfk_1` FOREIGN KEY (`object`) REFERENCES `dict_object` (`object`) ON UPDATE CASCADE,
  CONSTRAINT `dict_swf_object_ibfk_2` FOREIGN KEY (`ml_swf`) REFERENCES `dict_lang` (`object`) ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of dict_swf_object
-- ----------------------------
INSERT INTO `dict_swf_object` VALUES ('location_1', 'location_1_swf');
INSERT INTO `dict_swf_object` VALUES ('location_2', 'location_2_swf');
INSERT INTO `dict_swf_object` VALUES ('location_3', 'location_3_swf');
INSERT INTO `dict_swf_object` VALUES ('location_4', 'location_4_swf');
INSERT INTO `dict_swf_object` VALUES ('location_5', 'location_5_swf');
INSERT INTO `dict_swf_object` VALUES ('location_6', 'location_6_swf');

-- ----------------------------
-- Table structure for `global`
-- ----------------------------
DROP TABLE IF EXISTS `global`;
CREATE TABLE `global` (
  `param` varchar(25) NOT NULL,
  `value` varchar(55) NOT NULL,
  PRIMARY KEY (`param`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of global
-- ----------------------------
INSERT INTO `global` VALUES ('save_period', '30');
INSERT INTO `global` VALUES ('unload_period', '14400');

-- ----------------------------
-- Table structure for `logins`
-- ----------------------------
DROP TABLE IF EXISTS `logins`;
CREATE TABLE `logins` (
  `uid` int(20) unsigned NOT NULL AUTO_INCREMENT,
  `social_id` bigint(20) unsigned NOT NULL DEFAULT '0',
  `social_net_id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `db_id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  `online_server_id` tinyint(3) unsigned NOT NULL DEFAULT '0',
  PRIMARY KEY (`uid`),
  KEY `online` (`online_server_id`) USING BTREE,
  KEY `owner_db_id_index` (`db_id`) USING BTREE,
  KEY `social_net-social_id` (`social_id`,`social_net_id`) USING BTREE,
  CONSTRAINT `db_fk` FOREIGN KEY (`db_id`) REFERENCES `db_desc` (`db_id`) ON UPDATE CASCADE,
  CONSTRAINT `online_fk` FOREIGN KEY (`online_server_id`) REFERENCES `server_desc` (`server_id`) ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=51 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of logins
-- ----------------------------
INSERT INTO `logins` VALUES ('0', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('1', '3597077', '0', '1', '1');
INSERT INTO `logins` VALUES ('2', '4756198', '0', '1', '1');
INSERT INTO `logins` VALUES ('3', '166170586', '0', '1', '0');
INSERT INTO `logins` VALUES ('4', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('5', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('6', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('7', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('8', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('9', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('10', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('11', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('12', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('13', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('14', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('15', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('16', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('17', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('18', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('19', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('20', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('21', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('22', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('23', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('24', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('25', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('26', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('27', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('28', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('29', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('30', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('31', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('32', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('33', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('34', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('35', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('36', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('37', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('38', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('39', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('40', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('41', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('42', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('43', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('44', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('45', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('46', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('47', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('48', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('49', '0', '0', '0', '0');
INSERT INTO `logins` VALUES ('50', '0', '0', '0', '0');

-- ----------------------------
-- Table structure for `server_desc`
-- ----------------------------
DROP TABLE IF EXISTS `server_desc`;
CREATE TABLE `server_desc` (
  `server_id` tinyint(3) unsigned NOT NULL,
  `online_pid` smallint(3) unsigned NOT NULL,
  `active` tinyint(3) unsigned NOT NULL,
  `daemon_dir` tinytext NOT NULL,
  `listen_ip` tinytext NOT NULL,
  `port` smallint(5) unsigned NOT NULL,
  `http_port` smallint(5) unsigned NOT NULL,
  `ext_port` smallint(5) unsigned NOT NULL,
  `daemon_user` tinytext NOT NULL,
  `error_log_path` tinytext NOT NULL,
  `srv_log_path` tinytext NOT NULL,
  `dbg_lvl` tinyint(3) unsigned NOT NULL,
  `num_net_threads` tinyint(3) unsigned NOT NULL,
  `num_worker_threads` tinyint(3) unsigned NOT NULL,
  `version_control_system_name` tinytext NOT NULL,
  PRIMARY KEY (`server_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of server_desc
-- ----------------------------
INSERT INTO `server_desc` VALUES ('0', '0', '0', 'NOP-SERVER', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0');
INSERT INTO `server_desc` VALUES ('1', '10367', '1', '/home/nonametr/projects/voodoo/server/build', '0.0.0.0', '20000', '50000', '30000', 'nonametr', 'err_srv.log', 'log_srv.log', '5', '3', '10', 'GIT');
INSERT INTO `server_desc` VALUES ('2', '0', '1', '/home/nonametr/projects/voodoo/server/game_server', '0.0.0.0', '20000', '50000', '30000', 'nonametr', 'err_srv.log', 'log_srv.log', '5', '3', '10', 'GIT');

-- ----------------------------
-- Table structure for `social_desc`
-- ----------------------------
DROP TABLE IF EXISTS `social_desc`;
CREATE TABLE `social_desc` (
  `social_net_id` tinyint(3) unsigned NOT NULL AUTO_INCREMENT,
  `social_net_name` set('VK','MM','OK','FB') NOT NULL,
  `app_id` tinytext NOT NULL,
  `app_secret` tinytext NOT NULL,
  `login_path` tinytext NOT NULL,
  `iframe` mediumtext NOT NULL,
  `iframe_friend_rq` mediumtext NOT NULL,
  PRIMARY KEY (`social_net_id`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of social_desc
-- ----------------------------
INSERT INTO `social_desc` VALUES ('0', 'VK', '2834556', 'dS5vuTak4E5g1L7XZC0t', 'GET /voodoo3_vk_login', '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\r\r\n  <head>\r\r\n    <title>Хроники Вуду</title>\r\r\n    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\r\n	<style type=\"text/css\" media=\"screen\">\r\r\n	html, body { height:100%; background-color: #ffffff;}\r\r\n	body { margin:0; padding:0; overflow:hidden; }\r\r\n	</style>\r\r\n    <script type=\"text/javascript\" src=\"http://vkontakte.ru/js/api/xd_connection.js?2\"></script>\r\r\n    <script type=\"text/javascript\" src=\"http://voodoo.jedgames.com/js/swfobject.js\"></script>    \r\r\n    <script type=\"text/javascript\" src=\"http://userapi.com/js/api/openapi.js?33\"></script>\r\r\n\r\r\n    <script type=\"text/javascript\">\r\r\nvar a;\r\r\nfunction stopWidget()\r\r\n{\r\r\n	//a = NULL;\r\r\n	//allert(a);\r\r\n}\rwindow.onload = (function() {     \r\r\n        VK.init(function() {\r\r\n        });\r	VK.addCallback(\"onWindowBlur\", onWindowBlur);\r\r\n	VK.addCallback(\"onWindowFocus\", onWindowFocus);﻿\r\r\n	a = VK.Widgets.Group(\"VKGR\", {mode: 2, width: \"730\", height: \"350\"}, 28502419);\r\r\n	//setTimeout(stopWidget, 2000);    \r\r\n});\r\r\nfunction addWallPost(id, value)\r\r\n{\r\r\n\r\r\n	if (value == \"I_NEED_YOUR_HELP\")	{value  = \"photo139860024_264486370\";}\r\r\n	else if (value == \"I_WIN_BOSS\")		{value  = \"photo139860024_264643661\";}\r\r\n	else if (value == \"I_MASTER_LOCATION\")	{value  = \"photo139860024_264486368\";}\r\r\n	else if (value == \"I_LEVEL_UP\")		{value  = \"photo139860024_264609348\";}\r\r\n	else if (value == \"I_POWERUP_YOU\") {value = \"photo139860024_266075969\";}\r\r\n	else if (value == \"SHRON_FOR_FRIEND\") {value = \"photo139860024_266080622\";}\r\r\n	else if (value == \"CALL_NOAPP_FRIEND\") {value = \"photo139860024_266510983\";}\r\r\n	else if (value == \"TNX_A_FRIEND\") {value = \"photo139860024_267892667\";}	\r\r\n	else if (value == \"I_WIN_PVE\") {value = \"photo139860024_268843495\";}\r\r\n	\r\r\n	VK.api(\"wall.post\",{owner_id:id, attachment:value});\r\r\n}\r\r\nfunction onWindowBlur()\r\r\n{\r\r\n    var a = document.getElementById(\'flashContent\'); \r\r\n    a.style.margin = \"-10000px\";\r\r\n}            \r\r\nfunction onWindowFocus()\r\r\n{\r\r\n    var a = document.getElementById(\'flashContent\'); \r\r\n    a.style.margin = \"0px\";\r\r\n}    \r\r\n\r\r\nfunction showInviteBox()\r\r\n{\r\r\n\r\r\nVK.callMethod(\"showInviteBox\");\r\r\n}\r\r\n\r\r\nfunction callHelp()\r\r\n{\r\r\n	window.open(\'http://vkontakte.ru/topic-28502419_25019837\',\'callHelpWin\');\r\r\n}\r\r\nfunction callGroup()\r\r\n{\r\r\n	window.open(\'http://vkontakte.ru/club28502419\',\'callGroupWin\');\r\r\n}\r\r\nfunction callFunction(func, data, upData)\r\r\n{\r\r\n    VK.callMethod(func, data, upData);       		\r\r\n}\r\r\nfunction crashReload()\r\r\n{\r\r\n	settimeout(realReload, 500);	\r\r\n}\r\r\nfunction realReload()\r\r\n{\r\r\n	location.reload(true);\r\r\n}\r\r\nvar flashvars = {\r\r\n};\r\r\nvar swf_path = \"http://voodoo.jedgames.com/HOGAMEREAL.swf\";\r\r\nvar swf_path_helper = \"http://cs10708.vkontakte.ru/\";\r\r\nswfobject.embedSWF(swf_path, \"flashContent\", \"760\", \"570\", \"1.0.19\", \"http://www.adobe.com/go/getflash\", flashvars);\r\r\nswfobject.embedSWF(swf_path_helper, \"flashContent_helper\", \"1\", \"1\", \"1.0.19\", \"http://www.adobe.com/go/getflash\", flashvars);\r\r\n  </script>\r\r\n  </head>\r\r\n  <body>\r\r\n        <div id=\"flashContent\">\r\r\n                <center>\r\r\n                        <p>\r\r\n                                <b>загрузка...</b><h6>(если долго ничего не происходит обновите страницу)</h6>\r\r\n                        </p>\r\r\n                        <div stile = \"align:center;v-align:middle\">\r\r\n                                <a href=\"http://www.adobe.com/go/getflash\" target = \"_blank\"><img src=\"http://www.adobe.com/products/flex/images/rightrail_platformlockup.jpg\"><br>Установить Flash Player</a>\r\r\n                        </div>\r\r\n                </center>\r\r\n        </div>\r\r\n        <div id=\"flashContent_helper\">\r\r\n                <center>\r\r\n                <p><b>загрузка...</b><h6>(если долго ничего не происходит обновите страницу)</h6></p>\r\r\n                <div stile = \"align:center;v-align:middle\"><a href=\"http://www.adobe.com/go/getflash\" target = \"_blank\"></div>\r\r\n                </center>\r\r\n        </div>\r\r\n\r\r\n        <!-- VK Widget -->\r\r\n        <div id=\"VKGR\" style=\"position:absolute; left:0px; top:675px; width:730px; height:350px; z-index:1\"></div>\r\r\n  </body>\r\r\n</html>', '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n\r\n<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\r\n\r\n  <head>\r\n\r\n    <title>Хроники Вуду</title>\r\n\r\n    <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n\r\n	<style type=\"text/css\" media=\"screen\">\r\n\r\n	html, body { height:100%; background-color: #ffffff;}\r\n\r\n	body { margin:0; padding:0; overflow:hidden; }\r\n\r\n	</style>\r\n\r\n    <script type=\"text/javascript\" src=\"http://vkontakte.ru/js/api/xd_connection.js?2\"></script>\r\n\r\n    <script type=\"text/javascript\" src=\"http://jedgames.com/swfobject.js\"></script>    \r\n\r\n    <script type=\"text/javascript\" src=\"http://userapi.com/js/api/openapi.js?33\"></script>\r\n\r\n<script type=\"text/javascript\">\r\n\r\n   function objectToString(o){\r\n    \r\n    var parse = function(_o){\r\n    \r\n        var a = [], t;\r\n        \r\n        for(var p in _o){\r\n        \r\n            if(_o.hasOwnProperty(p)){\r\n            \r\n                t = _o[p];\r\n                \r\n                if(t && typeof t == \"object\"){\r\n                \r\n                    a[a.length]= p + \":{ \" + arguments.callee(t).join(\", \") + \"}\";\r\n                    \r\n                }\r\n                else {\r\n                    \r\n                    if(typeof t == \"string\"){\r\n                    \r\n                        a[a.length] = [ p+ \": \\\"\" + t.toString() + \"\\\"\" ];\r\n                    }\r\n                    else{\r\n                        a[a.length] = [ p+ \": \" + t.toString()];\r\n                    }\r\n                    \r\n                }\r\n            }\r\n        }\r\n        \r\n        return a;\r\n        \r\n    }\r\n    \r\n    return \"{\" + parse(o).join(\", \") + \"}\";\r\n    \r\n}\r\nfunction post_to_url(path, params, method) {\r\n    method = method || \"post\"; // Set method to post by default, if not specified.\r\n\r\n    // The rest of this code assumes you are not using a library.\r\n    // It can be made less wordy if you use one.\r\n    var form = document.createElement(\"form\");\r\n    form.setAttribute(\"method\", method);\r\n    form.setAttribute(\"action\", path);\r\n\r\n \r\n            var hiddenField = document.createElement(\"input\");\r\n            hiddenField.setAttribute(\"type\", \"hidden\");\r\n            hiddenField.setAttribute(\"name\", \"friends_vk_req_friends_post\");\r\n            hiddenField.setAttribute(\"value\", objectToString(params));\r\n            form.appendChild(hiddenField);\r\n        \r\n    \r\n\r\n    document.body.appendChild(form);\r\n    form.submit();\r\n}\r\n\r\n\r\nwindow.onload = (function() {     \r\n\r\n        VK.init(function() {\r\n\r\n        });\r\n\r\nVK.api(\'friends.getAppUsers\', {},\r\nfunction(data)\r\n{\r\n    var t=data.response.length;\r\n    post_to_url(\"http://31.43.122.45/voodoo3_vk_friends_data\", data, \"post\");\r\n});\r\n\r\n\r\n});\r\n\r\n</script>\r\n</head>\r\n\r\n  <body>\r\n\r\n        <div id=\"flashContent\">\r\n\r\n                <center>\r\n\r\n                        <p>\r\n\r\n                                <b>загрузка...</b>\r\n\r\n                        </p>                        \r\n\r\n                </center>\r\n\r\n        </div>\r\n\r\n  </body>\r\n\r\n</html>');
INSERT INTO `social_desc` VALUES ('1', 'MM', '41243', 'fcaer34123', 'GET /voodoo3_mm_login', '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\n\r\n	<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\r\n\r\n 	 <head>\r\n\r\n		<title>Хроники Вуду</title>\r\n\r\n	<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\n\r\n<style type=\"text/css\" media=\"screen\">\r\n\r\n	html, body { height:100%; background-color: #ffffff;}\r\n\r\n	body { margin:0; padding:0; overflow:hidden; }\r\n\r\n</style>\r\n\r\n    \r\n\r\n<script type=\"text/javascript\" src=\"http://jedgames.com/swfobject.js\"></script>    \r\n\r\n	\r\n\r\n	\r\n\r\n<script src=\"http://api.odnoklassniki.ru/js/fapi.js\" type=\"text/javascript\"></script>\r\n\r\n	\r\n\r\n<link href=\"http://stg.odnoklassniki.ru/share/odkl_share.css\" rel=\"stylesheet\">\r\n\r\n<script src=\"http://stg.odnoklassniki.ru/share/odkl_share.js\" type=\"text/javascript\" >\r\n\r\n</script>	\r\n\r\n   \r\n\r\n<script type=\"text/javascript\">\r\n\r\n\r\n\r\n\r\n\r\nvar a;\r\n\r\nfunction stopWidget()			\r\n\r\n{\r\n\r\n	a = NULL;	\r\n\r\n	allert(a);\r\n\r\n}\r\n\r\n		\r\n\r\n\r\n\r\n//api_id = application_key \r\n\r\n //alert(\"API initialization try\");\r\n\r\n window.onload = (function() {  \r\n\r\n startinit();\r\n\r\n }\r\n\r\n );\r\n\r\n function startinit()\r\n\r\n {\r\n\r\n FAPI.init(\"http://api.odnoklassniki.ru/\", flashvars[\"secret\"],\r\n\r\n  function() {\r\n\r\n     // alert(\"API initialization success\");\r\n\r\n  }, function(error){\r\n\r\n     alert(\"API initialization failed\");\r\n\r\n  }); \r\n\r\n}\r\n\r\n \r\n\r\n\r\n\r\n\r\n\r\nfunction test(){\r\n\r\n	var request = {};\r\n\r\n	request[\'method\'] = \"stream.publish\";\r\n\r\n	request[\'uid\'] = \"126922343409\";\r\n\r\n	request[\'message\'] = \'Sample text\';\r\n\r\n	request[\'attachment\'] = \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\';\r\n\r\n	\r\n\r\n	\r\n\r\n	sig = FAPI.Util.calcSignature(request); \r\n\r\n\r\n\r\n	//alert(request[\'method\'] +\" : \"+ request[\'message\'] +\" : \"+  sig);	\r\n\r\n	FAPI.UI.showConfirmation(request[\'method\'], request[\'message\'], \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\', sig);\r\n\r\n}\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\nfunction addWallPost(id, value)\r\n\r\n{\r\n\r\n	var request = {};\r\n\r\n	request[\'method\'] = \"stream.publish\";\r\n\r\n	request[\'uid\'] = id;\r\n\r\n	request[\'message\'] = \'Sample text\';\r\n\r\n	\r\n\r\n	\r\n\r\n	if (value == \"I_NEED_YOUR_HELP\") {request[\'message\']  = \"Мне нужна твоя помощь!\";}\r\n\r\n else if (value == \"I_WIN_BOSS\")  {request[\'message\']  = \"УРА! Я победил командира!\";}\r\n\r\n else if (value == \"I_MASTER_LOCATION\") {request[\'message\']  = \"Я выполнил все задания на локации!\";}\r\n\r\n else if (value == \"I_LEVEL_UP\")  {request[\'message\']  = \"Я взял новый уровень!\";}\r\n\r\n else if (value == \"I_POWERUP_YOU\") {request[\'message\'] = \"Я качнул тебе бицуху, дружище!\";}\r\n\r\n else if (value == \"SHRON_FOR_FRIEND\") {request[\'message\'] = \"Лови схрон, друг!\";}\r\n\r\n else if (value == \"CALL_NOAPP_FRIEND\") {request[\'message\'] = \"Присоединяйся! Давай служить вместе!\";}\r\n\r\n else if (value == \"TNX_A_FRIEND\") {request[\'message\'] = \"Спасибо, друг\";}\r\n\r\n else if (value == \"I_WIN_PVE\") {request[\'message\'] = \"Я победил в бою!\";}\r\n\r\n	\r\n\r\n	\r\n\r\n	//FAPI.api(\"wall.post\",{owner_id:id, attachment:value});\r\n\r\n	\r\n\r\n\r\n\r\n	//request[\'attachment\'] = \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\';\r\n\r\n	\r\n\r\n	\r\n\r\n	sig = FAPI.Util.calcSignature(request); \r\n\r\n\r\n\r\n	//alert(request[\'method\'] +\" : \"+ request[\'message\'] +\" : \"+  sig);	\r\n\r\n	FAPI.UI.showConfirmation(request[\'method\'], request[\'message\'],  sig);\r\n\r\n}\r\n\r\nfunction onWindowBlur()\r\n\r\n{\r\n\r\n    var a = document.getElementById(\'flashContent\'); \r\n\r\n    a.style.margin = \"-10000px\";\r\n\r\n}            \r\n\r\nfunction onWindowFocus()\r\n\r\n{\r\n\r\n    var a = document.getElementById(\'flashContent\'); \r\n\r\n    a.style.margin = \"0px\";\r\n\r\n}    \r\n\r\nfunction callHelp()\r\n\r\n{\r\n\r\n	window.open(\'http://vkontakte.ru/topic-28502419_25019837\',\'callHelpWin\');\r\n\r\n}\r\n\r\nfunction callGroup()\r\n\r\n{\r\n\r\n	window.open(\'http://vkontakte.ru/club28502419\',\'callGroupWin\');\r\n\r\n}\r\n\r\n\r\n\r\n		//ApiManager.getInstance().getSocial().externalInterfaceCall(\"showPaymentBox\", [_data[\'type\'], _data[\'price\'],_data[\'count\'],_data[\'id\']]);\r\n\r\nfunction showPaymentBox(type, price, count, id)\r\n\r\n{\r\n\r\n		if(type == \"gold\") type = \"Реальной капусты\";\r\n\r\n		if(type == \"money\") type = \"Хавки\";\r\n\r\n		FAPI.UI.showPayment(\'Товар: (\'+count+\') \'+type, \'Количество:\' + count, id , (price * 7));\r\n\r\n			 //showPayment(\'Product Name\', \'Product Desctiption\', \'Product Code\', 10);	\r\n\r\n}\r\n\r\n\r\n\r\nfunction showPaymentBoxComplects(type, price, count, id){\r\n\r\n	FAPI.UI.showPayment(\'Товар: (\'+count+\')\'+type, \'Количество:\' + count, id , (price * 7));\r\n\r\n}\r\n\r\n\r\n\r\n\r\n\r\nfunction showInviteBox(){\r\n\r\n	FAPI.UI.showInvite(\'Прийди ко мне! Давай служить вместе!\', \'customAttr=customValue\');\r\n\r\n}\r\n\r\n\r\n\r\n\r\n\r\nfunction crashReload()\r\n\r\n{\r\n\r\n	settimeout(realReload, 500);	\r\n\r\n}\r\n\r\nfunction realReload()\r\n\r\n{\r\n\r\n	location.reload(true);\r\n\r\n}	\r\n\r\nvar  options = \"[{\\\"name\\\":\\\"\" + \'artem\' + \"\\\", \\\"price\\\":\\\"2\\\", \\\"code\\\":\\\"qCoins1\\\"},{\\\"name\\\":\\\"\" + \'artem\' + \"\\\", \\\"price\\\":\\\"3\\\", \\\"code\\\":\\\"qCoins2\\\"}]\";\r\n\r\nvar  permissions = \"[\\\"PUBLISH TO STREAM\\\",\\\"PHOTO CONTENT\\\" ]\";\r\n\r\n \r\n\r\n //Callback function\r\n\r\n //function API_callback(method, result, data){\r\n\r\n      //alert(\"Method \"+method+\" finished with result \"+result+\", \"+data);\r\n\r\n  //} 	\r\n\r\n	\r\n\r\nvar flashvars = {\r\n\r\n};\r\n\r\nvar swf_path = \"http://jedgames.com/PreloaderFactory.swf?kash_id=ssd3\";\r\n\r\nswfobject.embedSWF(swf_path, \"flashContent\", \"730\", \"675\", \"1.0.19\", \"http://www.adobe.com/go/getflash\", flashvars);\r\n\r\n    </script>\r\n\r\n  </head>\r\n\r\n  <body>\r\n\r\n   <!--<input type=\"button\" onclick=\"test();\"  value=\"Test\">\r\n\r\n  <input type=\"button\" onclick=\"FAPI.UI.showPermissions(permissions);\" value=\"Permissions\">\r\n\r\n<input type=\"button\" onclick=\"FAPI.UI.showInvite(\'Default text\', \'customAttr=customValue\');\" value=\"Invite\">\r\n\r\n<input type=\"button\" onclick=\"FAPI.UI.showNotification(\'Suggestion text\',\'customAttr=vValue\');\" value=\"Notification\">\r\n\r\n<input type=\"button\" onclick=\"FAPI.UI.showConfirmation(\'test.test\',\'Some text\',\'signature\');\" value=\"Show Confirmation\">\r\n\r\n<input type=\"button\" onclick=\"FAPI.UI.showPayment(\'\', \'dfsadfdsf\', \'qCoins\', \'0\', options,\'[]\',\'ok\', \'true\');\" value=\"Show Payment\">\r\n\r\n<input type=\"button\" onclick=\"FAPI.UI.setWindowSize(500, 500);\" value=\"Set Size\"> -->\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n    <div id=\"flashContent\">\r\n\r\n	<center>\r\n\r\n	      <p><b>загрузка...</b><h6>(если долго ничего не происходит обновите страницу)</h6></p>\r\n\r\n		<div stile = \"align:center;v-align:middle\"><a href=\"http://www.adobe.com/go/getflash\" target = \"_blank\"><img src=\"http://www.adobe.com/products/flex/images/rightrail_platformlockup.jpg\"><br>Установить Flash Player</a></div>\r\n\r\n	</center>\r\n\r\n    	</div>\r\n\r\n	<!-- VK Widget -->\r\n\r\n	<div id=\"vk_groups\" style=\"position:absolute; left:0px; top:730px; width:730px; height:350px; z-index:1\"></div>\r\n\r\n  </body>\r\n\r\n</html>', '');
INSERT INTO `social_desc` VALUES ('2', 'OK', '934124589', 'adsduopW22', 'GET /voodoo3_ok_login', '<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">\r\r\n	<html xmlns=\"http://www.w3.org/1999/xhtml\" lang=\"en\" xml:lang=\"en\">\r\r\n 	 <head>\r\r\n		<title>Хроники Вуду</title>\r\r\n	<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\" />\r\r\n<style type=\"text/css\" media=\"screen\">\r\r\n	html, body { height:100%; background-color: #ffffff;}\r\r\n	body { margin:0; padding:0; overflow:hidden; }\r\r\n</style>\r\r\n    \r\r\n<script type=\"text/javascript\" src=\"http://jedgames.com/swfobject.js\"></script>    \r\r\n	\r\r\n	\r\r\n<script src=\"http://api.odnoklassniki.ru/js/fapi.js\" type=\"text/javascript\"></script>\r\r\n	\r\r\n<link href=\"http://stg.odnoklassniki.ru/share/odkl_share.css\" rel=\"stylesheet\">\r\r\n<script src=\"http://stg.odnoklassniki.ru/share/odkl_share.js\" type=\"text/javascript\" >\r\r\n</script>	\r\r\n   \r\r\n<script type=\"text/javascript\">\r\r\n\r\r\n\r\r\nvar a;\r\r\nfunction stopWidget()			\r\r\n{\r\r\n	a = NULL;	\r\r\n	allert(a);\r\r\n}\r\r\n		\r\r\n\r\r\n//api_id = application_key \r\r\n //alert(\"API initialization try\");\r\r\n window.onload = (function() {  \r\r\n startinit();\r\r\n }\r\r\n );\r\r\n function startinit()\r\r\n {\r\r\n FAPI.init(\"http://api.odnoklassniki.ru/\", flashvars[\"secret\"],\r\r\n  function() {\r\r\n     // alert(\"API initialization success\");\r\r\n  }, function(error){\r\r\n     alert(\"API initialization failed\");\r\r\n  }); \r\r\n}\r\r\n \r\r\n\r\r\n\r\r\nfunction test(){\r\r\n	var request = {};\r\r\n	request[\'method\'] = \"stream.publish\";\r\r\n	request[\'uid\'] = \"126922343409\";\r\r\n	request[\'message\'] = \'Sample text\';\r\r\n	request[\'attachment\'] = \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\';\r\r\n	\r\r\n	\r\r\n	sig = FAPI.Util.calcSignature(request); \r\r\n\r\r\n	//alert(request[\'method\'] +\" : \"+ request[\'message\'] +\" : \"+  sig);	\r\r\n	FAPI.UI.showConfirmation(request[\'method\'], request[\'message\'], \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\', sig);\r\r\n}\r\r\n\r\r\n\r\r\n\r\r\nfunction addWallPost(id, value)\r\r\n{\r\r\n	var request = {};\r\r\n	request[\'method\'] = \"stream.publish\";\r\r\n	request[\'uid\'] = id;\r\r\n	request[\'message\'] = \'Sample text\';\r\r\n	\r\r\n	\r\r\n	if (value == \"I_NEED_YOUR_HELP\") {request[\'message\']  = \"Мне нужна твоя помощь!\";}\r\r\n else if (value == \"I_WIN_BOSS\")  {request[\'message\']  = \"УРА! Я победил командира!\";}\r\r\n else if (value == \"I_MASTER_LOCATION\") {request[\'message\']  = \"Я выполнил все задания на локации!\";}\r\r\n else if (value == \"I_LEVEL_UP\")  {request[\'message\']  = \"Я взял новый уровень!\";}\r\r\n else if (value == \"I_POWERUP_YOU\") {request[\'message\'] = \"Я качнул тебе бицуху, дружище!\";}\r\r\n else if (value == \"SHRON_FOR_FRIEND\") {request[\'message\'] = \"Лови схрон, друг!\";}\r\r\n else if (value == \"CALL_NOAPP_FRIEND\") {request[\'message\'] = \"Присоединяйся! Давай служить вместе!\";}\r\r\n else if (value == \"TNX_A_FRIEND\") {request[\'message\'] = \"Спасибо, друг\";}\r\r\n else if (value == \"I_WIN_PVE\") {request[\'message\'] = \"Я победил в бою!\";}\r\r\n	\r\r\n	\r\r\n	//FAPI.api(\"wall.post\",{owner_id:id, attachment:value});\r\r\n	\r\r\n\r\r\n	//request[\'attachment\'] = \'{\"caption\":\"Test\",\"media\":[{\"src\":\"image.jpg\",\"type\":\"image\"}]}\';\r\r\n	\r\r\n	\r\r\n	sig = FAPI.Util.calcSignature(request); \r\r\n\r\r\n	//alert(request[\'method\'] +\" : \"+ request[\'message\'] +\" : \"+  sig);	\r\r\n	FAPI.UI.showConfirmation(request[\'method\'], request[\'message\'],  sig);\r\r\n}\r\r\nfunction onWindowBlur()\r\r\n{\r\r\n    var a = document.getElementById(\'flashContent\'); \r\r\n    a.style.margin = \"-10000px\";\r\r\n}            \r\r\nfunction onWindowFocus()\r\r\n{\r\r\n    var a = document.getElementById(\'flashContent\'); \r\r\n    a.style.margin = \"0px\";\r\r\n}    \r\r\nfunction callHelp()\r\r\n{\r\r\n	window.open(\'http://vkontakte.ru/topic-28502419_25019837\',\'callHelpWin\');\r\r\n}\r\r\nfunction callGroup()\r\r\n{\r\r\n	window.open(\'http://vkontakte.ru/club28502419\',\'callGroupWin\');\r\r\n}\r\r\n\r\r\n		//ApiManager.getInstance().getSocial().externalInterfaceCall(\"showPaymentBox\", [_data[\'type\'], _data[\'price\'],_data[\'count\'],_data[\'id\']]);\r\r\nfunction showPaymentBox(type, price, count, id)\r\r\n{\r\r\n		if(type == \"gold\") type = \"Реальной капусты\";\r\r\n		if(type == \"money\") type = \"Хавки\";\r\r\n		FAPI.UI.showPayment(\'Товар: (\'+count+\') \'+type, \'Количество:\' + count, id , (price * 7));\r\r\n			 //showPayment(\'Product Name\', \'Product Desctiption\', \'Product Code\', 10);	\r\r\n}\r\r\n\r\r\nfunction showPaymentBoxComplects(type, price, count, id){\r\r\n	FAPI.UI.showPayment(\'Товар: (\'+count+\')\'+type, \'Количество:\' + count, id , (price * 7));\r\r\n}\r\r\n\r\r\n\r\r\nfunction showInviteBox(){\r\r\n	FAPI.UI.showInvite(\'Прийди ко мне! Давай служить вместе!\', \'customAttr=customValue\');\r\r\n}\r\r\n\r\r\n\r\r\nfunction crashReload()\r\r\n{\r\r\n	settimeout(realReload, 500);	\r\r\n}\r\r\nfunction realReload()\r\r\n{\r\r\n	location.reload(true);\r\r\n}	\r\r\nvar  options = \"[{\\\"name\\\":\\\"\" + \'artem\' + \"\\\", \\\"price\\\":\\\"2\\\", \\\"code\\\":\\\"qCoins1\\\"},{\\\"name\\\":\\\"\" + \'artem\' + \"\\\", \\\"price\\\":\\\"3\\\", \\\"code\\\":\\\"qCoins2\\\"}]\";\r\r\nvar  permissions = \"[\\\"PUBLISH TO STREAM\\\",\\\"PHOTO CONTENT\\\" ]\";\r\r\n \r\r\n //Callback function\r\r\n //function API_callback(method, result, data){\r\r\n      //alert(\"Method \"+method+\" finished with result \"+result+\", \"+data);\r\r\n  //} 	\r\r\n	\r\r\nvar flashvars = {\r\r\n};\r\r\nvar swf_path = \"http://jedgames.com/PreloaderFactory.swf?kash_id=ssd3\";\r\r\nswfobject.embedSWF(swf_path, \"flashContent\", \"730\", \"675\", \"1.0.19\", \"http://www.adobe.com/go/getflash\", flashvars);\r\r\n    </script>\r\r\n  </head>\r\r\n  <body>\r\r\n   <!--<input type=\"button\" onclick=\"test();\"  value=\"Test\">\r\r\n  <input type=\"button\" onclick=\"FAPI.UI.showPermissions(permissions);\" value=\"Permissions\">\r\r\n<input type=\"button\" onclick=\"FAPI.UI.showInvite(\'Default text\', \'customAttr=customValue\');\" value=\"Invite\">\r\r\n<input type=\"button\" onclick=\"FAPI.UI.showNotification(\'Suggestion text\',\'customAttr=vValue\');\" value=\"Notification\">\r\r\n<input type=\"button\" onclick=\"FAPI.UI.showConfirmation(\'test.test\',\'Some text\',\'signature\');\" value=\"Show Confirmation\">\r\r\n<input type=\"button\" onclick=\"FAPI.UI.showPayment(\'\', \'dfsadfdsf\', \'qCoins\', \'0\', options,\'[]\',\'ok\', \'true\');\" value=\"Show Payment\">\r\r\n<input type=\"button\" onclick=\"FAPI.UI.setWindowSize(500, 500);\" value=\"Set Size\"> -->\r\r\n\r\r\n\r\r\n\r\r\n\r\r\n\r\r\n    <div id=\"flashContent\">\r\r\n	<center>\r\r\n	      <p><b>загрузка...</b><h6>(если долго ничего не происходит обновите страницу)</h6></p>\r\r\n		<div stile = \"align:center;v-align:middle\"><a href=\"http://www.adobe.com/go/getflash\" target = \"_blank\"><img src=\"http://www.adobe.com/products/flex/images/rightrail_platformlockup.jpg\"><br>Установить Flash Player</a></div>\r\r\n	</center>\r\r\n    	</div>\r\r\n	<!-- VK Widget -->\r\r\n	<div id=\"vk_groups\" style=\"position:absolute; left:0px; top:730px; width:730px; height:350px; z-index:1\"></div>\r\r\n  </body>\r\r\n</html>', '');
INSERT INTO `social_desc` VALUES ('3', 'FB', '43522217459312', 'faf341123123', 'GET /voodoo3_fb_login', '', '');
