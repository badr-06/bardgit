SELECT name from pizzeria
where 1 not In (
  	SELECT pizzeria_id from person_visits
  	)

-- SELECT name from pizzeria
-- where not exists ( 
--   			SELECT 1 from person_visits 
--   				where pizzeria.id = person_visits.pizzeria_id 
-- 			 )