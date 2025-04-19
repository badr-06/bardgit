CREATE or REPLACE FUNCTION func_minimum(arr NUMERIC[])
RETURNs NUMERIC AS
$$
  SELECT min(ei) from UNNEST(arr) as ei;
$$
LANGUAGE sql;
 
SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);