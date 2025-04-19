CREATE or REPLACE FUNCTION fnc_person_visits_and_eats_on_date(pperson VARCHAR DEFAULT 'Dmitriy', pprice NUMERIC DEFAULT 500, 
                                                             pdate DATE DEFAULT '2022-01-08')
RETURNs TABLE(name VARCHAR) AS
$$
 BEGIN
  RETURN QUERY 
 	SELECT pizzeria.name as pizzeria_name from pizzeria
 	 join menu on menu.pizzeria_id = pizzeria.id
  	 join person_visits on person_visits.pizzeria_id = pizzeria.id
    	join person on person_visits.person_id = person.id
  WHERE person.name = pperson and person_visits.visit_date = pdate and menu.price < pprice;
 end;
$$
LANGUAGE 'plpgsql';

select *
from fnc_person_visits_and_eats_on_date(pprice := 800);

select *
from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');
