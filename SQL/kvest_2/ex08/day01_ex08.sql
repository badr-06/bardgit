SELECT pers_ord.order_date, 
	   concat( name, ' (age:', age, ')') as person_information
			from (SELECT person_id as id, order_date from person_order)
            as pers_ord NATURAL join person
				ORDER by order_date, person_information