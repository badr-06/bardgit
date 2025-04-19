SELECT person.name from person
	join person_order on person_order.person_id = person.id
    	join menu on person_order.menu_id = menu.id
        	where person.gender = 'male' 
            and (person.address like 'Moscow' or person.address like 'Samara' )
            and ( menu.pizza_name like 'pepperoni%' or menu.pizza_name like 'mushroom%' )
            ORDER by 1 desc