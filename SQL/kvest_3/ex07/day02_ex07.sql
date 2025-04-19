SELECT pizzeria.name as pizzeria_name from pizzeria
	join person_visits on person_visits.pizzeria_id = pizzeria.id 
    	join person on person.id = person_visits.person_id
        	JOIN menu ON menu.pizzeria_id = pizzeria.id
    		where person.name like 'Dmitriy' and visit_date = date '2022-01-08' and menu.price < 800