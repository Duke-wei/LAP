DROP DATABASE IF EXISTS xmldb;

CREATE DATABASE xmldb;

USE xmldb;

CREATE TABLE InfoM(
	id int NOT NULL auto_increment,
	appName varchar(20) NULL,
	totalSourceBytes int NULL,
	totalDestinationBytes int NULL,
	totalDestinationPackets int NULL,
	totalSourcePackets int NULL,
	sourcePayloadAsBase64 varchar(1200) NULL,
	sourcePayloadAsUTF varchar(1200) NULL,
	destinationPayloadAsBase64 varchar(1200) NULL,
	destinationPayloadAsUTF varchar(1200) NULL,
	direction varchar(20) NULL,
	sourceTCPFlagsDescription varchar(20) NULL,
	destinationTCPFlagsDescription varchar(20) NULL,
	source varchar(20) NULL,
	protocolName varchar(20) NULL,
	sourcePort int NULL,
	destination varchar(20) NULL,
	destinationPort int NULL,
	startDateTime datetime NULL,
	stopDateTime datetime NULL,
	Tag varchar(10) NULL,
	primary key ( id )
)ENGINE=InnoDB DEFAULT CHARSET=gbk;

http://blog.chinaunix.net/uid-20577907-id-3037904.html
