SELECT pz.name as pizzeria_name from
(
  SELECT pizzeria.name FROM pizzeria
	join menu on menu.pizzeria_id = pizzeria.id
		JOIN person_order on menu.id = person_order.menu_id
        	join person on person_order.person_id = person.id and person.gender = 'female'
EXCEPT
SELECT pizzeria.name FROM pizzeria
	join menu on menu.pizzeria_id = pizzeria.id
		JOIN person_order on menu.id = person_order.menu_id
        	join person on person_order.person_id = person.id and person.gender = 'male'
) as pz
UNION
SELECT pz.name as pizzeria_name from 
(
    SELECT pizzeria.name FROM pizzeria
	join menu on menu.pizzeria_id = pizzeria.id
		JOIN person_order on menu.id = person_order.menu_id
        	join person on person_order.person_id = person.id and person.gender = 'male'
EXCEPT
SELECT pizzeria.name FROM pizzeria
	join menu on menu.pizzeria_id = pizzeria.id
		JOIN person_order on menu.id = person_order.menu_id
        	join person on person_order.person_id = person.id and person.gender = 'female'
) as pz
order by pizzeria_name