drop database if  exists secureindex;
create database secureindex;
use secureindex;
drop table if exists T_DOC;
create table T_DOC(
       doc_id varchar(128) not null,
       doc_name varchar(128) not null default '',
       doc_index text,
       doc_o_index text,
       ciphertext longblob,
       primary key(doc_id)
)DEFAULT CHARACTER SET utf8 COLLATE utf8_bin,
ENGINE = INNODB;
