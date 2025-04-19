CREATE or REPLACE FUNCTION fnc_trg_person_update_audit()
RETUrNs TRIGGER AS
$$
 BEGIN
  INSERT into person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'U', old.id, old.name, old.age, old.gender, old.address);
    
    RETURN old;
 end;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER trg_person_update_audit
after UPDATE on person
for EACH ROW EXECUTE FUNCTION fnc_trg_person_update_audit();

UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;

select * from person_audit;