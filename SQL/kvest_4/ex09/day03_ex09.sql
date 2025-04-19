INSERT into person_visits(id, person_id, pizzeria_id, visit_date)
VALUES(
	(SELECT max(id)+1 from person_visits),
  	(SELECT id from person where person.name like 'Denis'),
  	(SELECT id from pizzeria WHERE pizzeria.name like 'Dominos'),
  	'2022-02-24'
	),
    (
  	(SELECT max(id)+2 from person_visits),
  	(select id from person where person.name like 'Irina'),
  	(SELECT id from pizzeria where pizzeria.name like 'Dominos'),
  	'2022-02-24'
	)