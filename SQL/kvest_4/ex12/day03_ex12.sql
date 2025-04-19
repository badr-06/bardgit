INSERT into person_order(id, person_id, menu_id, order_date)
	SELECT
    	( SELECT max(id) FROM person_order )+person_id as ID,
        person_id,
        ( SELECT id from menu where menu.pizza_name like 'greek pizza' ),
        '2022-02-25'
    from
		GENERATE_SERIES((SELECT min(id) from person), (SELECT max(id) from person)) as person_id
        
	