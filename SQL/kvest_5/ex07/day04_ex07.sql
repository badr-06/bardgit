INSERT into person_visits(id, person_id, pizzeria_id, visit_date)
VALUES (
  	(SELECT max(id)+1 from person_visits), 
  	(SELECT id from person where person.name like 'Dmitriy'),
	(SELECT pizzeria.id from pizzeria
	join menu on pizzeria.id = menu.pizzeria_id
	where menu.price < 800 and pizzeria.name Not like 'Papa Johns'
    limit 1),
  	'2022-01-08'
	)
--создаем еще одно посещения дмитрия

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats

--обновляем состояние данных