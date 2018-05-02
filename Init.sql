create table user_info
(
	user_id char(6) primary key,
	user_name varchar[10] not null,
	user_psw varchar[10] not null,
	user_account varchar[10] not null,
	user_department varchar[15] not null,
	user_beizhu varchar[15] not null,
	user_state char(1),
	user_type varchar(100)--用户类型
);
insert into user_info values ("1001","admin","123456","xiaoli","办公室","null",'1',"系统管理员");
insert into user_info values ("1002","zhangsan","123456","xiaoli","办公室","null",'1',"系统管理员");
insert into user_info values ("1003","lisi","123456","xiaoli","办公室","null",'1',"系统管理员");
insert into user_info values ("1004","wangwu","123456","xiaowu","办公室","null",'1',"业务管理员");
insert into user_info values ("1005","wan","123456","xiaoniu","技术部","null",'1',"业务管理员");
insert into user_info values ("1006","xiaoli","123456","xixi","技术部","null",'1',"业务管理员");
insert into user_info values ("1007","wanwan","123456","xiaoha","办公室","null",'1',"业务管理员");
insert into user_info values ("1008","xiaohong","123456","xiaohong","办公室","null",'1',"操作员");

create table user_role
(
	user_id char(6) ,	
	role_id char(6)
);
insert into  user_role values ("1001","1001");
insert into  user_role values ("1002","1001");
insert into  user_role values ("1003","1003");
insert into  user_role values ("1004","1004");
insert into  user_role values ("1005","1001");
insert into  user_role values ("1006","1001");
insert into  user_role values ("1007","1003");
insert into  user_role values ("1008","1004");




create table role_info
(
	role_id char(6) ,	
	role_name varchar(30)
);
insert into role_info values ("1001","系统管理员");
insert into role_info values ("1002","业务管理员");
insert into role_info values ("1003","操作员");

--角色权限表
create table role_power
(
	role_id char(6),	
	menu_id varchar(6)
);
insert into  role_power values ("1001","1001");

insert into  role_power values ("1001","1002");

insert into  role_power values ("1001","1003");

insert into  role_power values ("1001","1004");
insert into  role_power values ("1001","1005");

insert into  role_power values ("1002","1001");
insert into  role_power values ("1002","1002");
insert into  role_power values ("1002","1003");
insert into  role_power values ("1002","1004");
insert into  role_power values ("1002","1005");

insert into  role_power values ("1003","1004");
insert into  role_power values ("1003","1005");

--菜单表
create table menu_info
(	
	menu_id varchar(6) ,
	menu_name varchar(30),
	menu_ftid varchar(6),
	menu_tate char(1) 
);
insert into menu_info values ("1001","系统管理",NULL,'1');
insert into menu_info values ("1002","客户端管理",NULL,'1');
insert into menu_info values ("1003","视频管理",NULL,'1');
insert into menu_info values ("1004","报表统计",NULL,'1');
insert into menu_info values ("1005","退出登录",NULL,'1');

insert into menu_info values ("1006","组织管理","1001",'1');
insert into menu_info values ("1007","用户管理","1001",'1');
insert into menu_info values ("1008","参数设置","1001",'1');

insert into menu_info values ("1009","客户端用户管理","1002",'1');
insert into menu_info values ("1010","用户点播管理","1002",'1');


insert into menu_info values ("1011","频道管理","1003",'1');
insert into menu_info values ("1012","分类信息管理","1003",'1');
insert into menu_info values ("1013","地区信息管理","1003",'1');
insert into menu_info values ("1014","视频信息管理","1003",'1');


insert into menu_info values ("1015","点播报表","1004",'1');

insert into menu_info values ("1016","注    销","1005",'1');
insert into menu_info values ("1017","退    出","1005",'1');
