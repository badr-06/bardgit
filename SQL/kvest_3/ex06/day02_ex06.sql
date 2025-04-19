SELECT menu.pizza_name, pizzeria.name from menu
	join pizzeria on menu.pizzeria_id = pizzeria.id
    	join (
        	SELECT menu_id from person_order
          		join person on person_order.person_id = person.id 
          		where person.name like 'Denis' or person.name like 'Anna'
        ) as person_order on person_order.menu_id = menu.id
        
  ORDER by 1, 2