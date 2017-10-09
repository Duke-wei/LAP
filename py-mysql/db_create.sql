DROP DATABASE IF EXISTS pro;

CREATE DATABASE pro;

USE pro;

CREATE TABLE message(
	id int NOT NULL auto_increment,
	savetime datetime DEFAULT CURRENT_TIMESTAMP,
	username varchar(30) NULL,
	ft_one int NULL,
	ft_two int NULL,
	ft_three int NULL,
	ft_four int NULL,
	ft_five int NULL,
	problem varchar(100) NULL,
	primary key ( id )
)ENGINE=InnoDB DEFAULT CHARSET=gbk;

INSERT INTO message (username,problem) values ('we','故障');

select * from message into outfile '~/problem.csv' FIELDS TERMINATED BY '|';
存储在/var/lib/mysql/datebase_name/

update message,problem set message.problem=problem.proid where message.username=problem.username;
