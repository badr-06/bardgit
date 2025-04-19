SELECT pizzeria.name FROM pizzeria
	JOIN person_visits on person_visits.pizzeria_id = pizzeria.id
    	join person on person.id = person_visits.person_id and person.name like 'Andrey'
EXCEPT
SELECT pizzeria.name from pizzeria
	join menu on menu.pizzeria_id = pizzeria.id
    	JOIN person_order on person_order.menu_id = menu.id
        	join person on person_order.person_id = person.id and person.name like 'Andrey'