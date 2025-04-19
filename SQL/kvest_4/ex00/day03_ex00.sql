SELECT menu.pizza_name, menu.price, pizzeria.name, person_visits.visit_date from menu
	join pizzeria on menu.pizzeria_id = pizzeria.id
    	join person_visits on person_visits.pizzeria_id = pizzeria.id
         join person on person.id = person_visits.person_id
        where menu.price BETWEEN 800 and 1000 and person.name = 'Kate'
        ORDER by 1, 2, 3
        