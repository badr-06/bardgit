drop FUNCTION fnc_persons_female();
drop FUNCTION fnc_persons_male();

CREATE or REPLACE FUNCTION fnc_persons(pgender VARCHAR(6) DEFAULT 'female')
RETURNs SETOF person AS
$$
 SELECT * from person WHERE gender In(pgender);
$$
LANGUAGE sql;

select *
from fnc_persons(pgender := 'male');

select *
from fnc_persons();