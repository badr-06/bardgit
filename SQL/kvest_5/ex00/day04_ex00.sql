CREATE VIEW v_persons_female AS
SELECT *
from person
where person.gender like 'female';

CREATE VIEW v_persons_male AS
SELECT *
from person
where person.gender like 'male';