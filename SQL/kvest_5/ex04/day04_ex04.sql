CREATE view v_symmetric_union as
( 
  SELECT person_id from person_visits pv WHERE pv.visit_date = date '2022-01-02'
  EXCEPT
  SELECT person_id from person_visits pv WHERE pv.visit_date = date '2022-01-06'
)
UNION
( 
  SELECT person_id from person_visits pv WHERE pv.visit_date = date '2022-01-06'
  EXCEPT
  SELECT person_id from person_visits pv WHERE pv.visit_date = date '2022-01-02' 
)