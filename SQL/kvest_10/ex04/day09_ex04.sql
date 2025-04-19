CREATE or REPLACE FUNCTION fnc_persons_female()
RETURNs SETOF person AS
$$
 SELECT * from person WHERE gender = 'female';
$$
LANGUAGE sql;

CREATE or REPLACE FUNCTION fnc_persons_male()
RETURNs SETOF person AS
$$
 SELECT * from person WHERE gender = 'male';
$$
LANGUAGE sql;

select * from fnc_persons_female();
select * from fnc_persons_male();