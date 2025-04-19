CREATE or REPLACE FUNCTION fnc_trg_person_delete_audit()
RETUrNs TRIGGER AS
$$
 BEGIN
  INSERT into person_audit(created, type_event, row_id, name, age, gender, address) VALUES
  	(CURRENT_TIMESTAMP, 'D', old.id, old.name, old.age, old.gender, old.address);
    
    RETURN old;
 end;
$$
LANGUAGE 'plpgsql';

CREATE TRIGGER trg_person_delete_audit
after DELETE on person
for EACH ROW EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;
SELECT * from person_audit