drop TRIGGER trg_person_delete_audit on person;
drop TRIGGER trg_person_update_audit on person;
drop TRIGGER trg_person_insert_audit on person;

drop FUNCTION fnc_trg_person_insert_audit();
drop FUNCTION fnc_trg_person_update_audit();
drop FUNCTION fnc_trg_person_delete_audit();

TRUNCATE TABLE person_audit;

CREATE or REPLACE FUNCTION fnc_trg_person_audit()
RETURNs TRIGGER AS
$$
 BEGIN
  if TG_OP = 'INSERT' THEN
  	INSERT INTO person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name, NEW.age, new.gender, new.address);
  ELSEIF TG_OP = 'UPDATE' THEN
  	INSERT into person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'U', old.id, old.name, old.age, old.gender, old.address);
  ELSEIF TG_OP = 'DELETE' THEN
    iNSERT into person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'D', old.id, old.name, old.age, old.gender, old.address);
  end if;
  
  RETURN new;
 end;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER trg_person_audit
after INSERT or UPDATE or DELETE on person
for EACH row EXECUTE FUNCTION fnc_trg_person_audit();

INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk');
UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;
DELETE FROM person WHERE id = 10;

select * from person_audit order by created;