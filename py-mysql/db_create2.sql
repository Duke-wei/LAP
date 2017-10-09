
USE pro;

CREATE TABLE message(
	id int NOT NULL auto_increment,
	savetime datetime DEFAULT CURRENT_TIMESTAMP,
	username varchar(30) NULL,
	f1 int NULL,
	f2 int NULL,
	f3 int NULL,
	f4 int NULL,
	f5 int NULL,
	f6 int NULL,
	f7 int NULL,
	f8 int NULL,
	f9 int NULL,
	f10 int NULL,
	f11 int NULL,
	f12 int NULL,
	f13 int NULL,
	f14 int NULL,
	f15 int NULL,
	problem int NULL,
	primary key ( id )
)ENGINE=InnoDB DEFAULT CHARSET=gbk;

