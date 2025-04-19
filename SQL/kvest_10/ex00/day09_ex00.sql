CREATE TABLE person_audit (
	created	TIMESTAMP WITH TIME ZONE DEFAULT CURRENT_TIMESTAMP NOT NULL,
	type_event CHAR(1) DEFAULT 'I' NOT NULL,
	row_id bigint NOT NULL,
	name varchar,
	age integer,
	gender varchar,
	address varchar,
  	CONSTRAINT ch_type_event CHECK (type_event IN ('I', 'D', 'U'))
);

CREATE or REPLACE FUNCTION fnc_trg_person_insert_audit() 
RETURNS TRIGGER as 
$$
 BEGIN
  INSERT INTO person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name, NEW.age, new.gender, new.address);
    
    RETURN NEW;
 END;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER trg_person_insert_audit
AFTER INSERT on person
for EACH row EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');
select * from person_audit;