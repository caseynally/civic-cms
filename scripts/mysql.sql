---------------------------------------------------------------------
-- Identify all the departments of the city
---------------------------------------------------------------------
create table departments (
	id int unsigned not null primary key auto_increment,
	name varchar(50) not null unique
) engine=InnoDB;

---------------------------------------------------------------------
-- User tables
---------------------------------------------------------------------
create table users (
  id int(10) unsigned not null primary key auto_increment,
  username varchar(30) not null,
  password varchar(32) default null,
  authenticationMethod varchar(40) not null default 'LDAP',
  firstname varchar(128) not null,
  lastname varchar(128) not null,
  department_id int unsigned not null,
  email varchar(255) not null,
  unique key (username),
  foreign key (department_id) references departments(id)
) engine=InnoDB;

create table roles (
  id int(10) unsigned not null primary key auto_increment,
  role varchar(30) not null unique
) engine=InnoDB;
insert roles set role='Administrator';
insert roles set role='Webmaster';
insert roles set role='Publisher';
insert roles set role='Content Creator';

create table user_roles (
  user_id int(10) unsigned not null,
  role_id int(10) unsigned not null,
  primary key  (user_id,role_id),
  foreign key (user_id) references users (id),
  foreign key (role_id) references roles (id)
) engine=InnoDB;

---------------------------------------------------------------------
-- Document tables
---------------------------------------------------------------------
create table documents (
  id int(10) unsigned not null primary key auto_increment,
  title varchar(128) not null,
  created timestamp not null default 0,
  modified timestamp default CURRENT_TIMESTAMP on update CURRENT_TIMESTAMP,
  modifiedBy int unsigned not null,
  department_id int unsigned not null,
  foreign key (modifiedBy) references users(id),
  foreign key (department_id) references departments(id)
) engine=InnoDB;

create table document_watches (
	document_id int unsigned not null,
	user_id int unsigned not null,
	primary key (document_id,user_id),
	foreign key (document_id) references documents(id),
	foreign key (user_id) references users(id)
) engine=InnoDB;
---------------------------------------------------------------------
-- Section tables
---------------------------------------------------------------------
create table sections (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null unique,
  department_id int unsigned not null,
  document_id int unsigned not null,
  foreign key (department_id) references departments(id),
  foreign key (document_id) references documents(id)
) engine=InnoDB;

create table section_parents (
  section_id int(10) unsigned not null,
  parent_id int(10) unsigned not null,
  foreign key (section_id) references sections (id),
  foreign key (parent_id) references sections (id)
) engine=InnoDB;

create table sectionIndex (
  section_id int(10) unsigned not null,
  preOrder int(10) unsigned default null,
  postOrder int(10) unsigned default null,
  foreign key (section_id) references sections (id)
) engine=InnoDB;

create table document_sections (
  document_id int(10) unsigned not null,
  section_id int(10) unsigned not null,
  foreign key (document_id) references documents (id),
  foreign key (section_id) references sections (id)
) engine=InnoDB;


---------------------------------------------------------------------
-- Facet tables
---------------------------------------------------------------------
create table facets (
  id int(10) unsigned not null primary key auto_increment,
  name varchar(50) not null unique
) engine=InnoDB;

create table section_facets (
	section_id int unsigned not null,
	facet_id int unsigned not null,
	primary key (section_id,facet_id),
	foreign key (section_id) references sections(id),
	foreign key (facet_id) references facets(id)
) engine=InnoDB;

create table document_facets (
  document_id int(10) unsigned not null,
  facet_id int(10) unsigned not null,
  primary key (document_id,facet_id),
  foreign key (document_id) references documents (id),
  foreign key (facet_id) references facets (id)
) engine=InnoDB;



---------------------------------------------------------------------
-- Widgets
---------------------------------------------------------------------
create table widgets (
	name varchar(128) not null primary key
) engine=InnoDB;

create table section_widgets (
	section_id int unsigned not null,
	widget_name varchar(128) not null,
	layout_order tinyint(2) unsigned not null,
	primary key (section_id,widget_name),
	unique (section_id,layout_order),
	foreign key (section_id) references sections(id),
	foreign key (widget_name) references widgets(name)
) engine=InnoDB;

---------------------------------------------------------------------
-- Languages
---------------------------------------------------------------------
create table languages (
	code char(2) not null primary key,
	english varchar(128) not null,
	native varchar(128) not null
) engine=InnoDB CHARACTER SET utf8;
insert languages values
('en','English','English'),
('fr','French','Français'),
('es','Spanish','Español'),
('de','German','Deutsch'),
('it','Italian','Italiano'),
('ko','Korean','한국어'),
('ja','Japanese','日本語'),
('zh','Chinese','中文');
