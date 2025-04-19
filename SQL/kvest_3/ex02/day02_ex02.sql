SELECT COALESCE(person.name, '-') as person_name, visit_date as visit_date,
COALESCE(pizzeria.name, '-') as pizzeria_name from person
	full OUTER join (
  	SELECT visit_date, person_id, pizzeria_id from person_visits where visit_date BETWEEN DATE '2022-01-01' and DATE '2022-01-03'
  ) as person_visits on person.id = person_visits.person_id
    	FULL outer join pizzeria on pizzeria.id = person_visits.pizzeria_id
order by person_name, visit_date, pizzeria_name
        	