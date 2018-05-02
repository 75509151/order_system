create table user_info
(
	user_id char(6) primary key,
	user_name varchar[10] not null,
	user_psw varchar[10] not null,
	user_account varchar[10] not null,
	user_department varchar[15] not null,
	user_beizhu varchar[15] not null,
	user_state char(1),
	user_type varchar(100)--�û�����
);
insert into user_info values ("1001","admin","123456","xiaoli","�칫��","null",'1',"ϵͳ����Ա");
insert into user_info values ("1002","zhangsan","123456","xiaoli","�칫��","null",'1',"ϵͳ����Ա");
insert into user_info values ("1003","lisi","123456","xiaoli","�칫��","null",'1',"ϵͳ����Ա");
insert into user_info values ("1004","wangwu","123456","xiaowu","�칫��","null",'1',"ҵ�����Ա");
insert into user_info values ("1005","wan","123456","xiaoniu","������","null",'1',"ҵ�����Ա");
insert into user_info values ("1006","xiaoli","123456","xixi","������","null",'1',"ҵ�����Ա");
insert into user_info values ("1007","wanwan","123456","xiaoha","�칫��","null",'1',"ҵ�����Ա");
insert into user_info values ("1008","xiaohong","123456","xiaohong","�칫��","null",'1',"����Ա");

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
insert into role_info values ("1001","ϵͳ����Ա");
insert into role_info values ("1002","ҵ�����Ա");
insert into role_info values ("1003","����Ա");

--��ɫȨ�ޱ�
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

--�˵���
create table menu_info
(	
	menu_id varchar(6) ,
	menu_name varchar(30),
	menu_ftid varchar(6),
	menu_tate char(1) 
);
insert into menu_info values ("1001","ϵͳ����",NULL,'1');
insert into menu_info values ("1002","�ͻ��˹���",NULL,'1');
insert into menu_info values ("1003","��Ƶ����",NULL,'1');
insert into menu_info values ("1004","����ͳ��",NULL,'1');
insert into menu_info values ("1005","�˳���¼",NULL,'1');

insert into menu_info values ("1006","��֯����","1001",'1');
insert into menu_info values ("1007","�û�����","1001",'1');
insert into menu_info values ("1008","��������","1001",'1');

insert into menu_info values ("1009","�ͻ����û�����","1002",'1');
insert into menu_info values ("1010","�û��㲥����","1002",'1');


insert into menu_info values ("1011","Ƶ������","1003",'1');
insert into menu_info values ("1012","������Ϣ����","1003",'1');
insert into menu_info values ("1013","������Ϣ����","1003",'1');
insert into menu_info values ("1014","��Ƶ��Ϣ����","1003",'1');


insert into menu_info values ("1015","�㲥����","1004",'1');

insert into menu_info values ("1016","ע    ��","1005",'1');
insert into menu_info values ("1017","��    ��","1005",'1');
