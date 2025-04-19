CREATE or REPLACE FUNCTION fnc_fibonacci(arr INTEGER DEFAULT 10)
RETURNS SETOF INTEGER AS
$$
 DECLARE
 	i INTEGER := 0;
    one INTEGER := 0;
    two INTEGER := 1;
 BEGIN
 		RETURN NEXT one;
        RETURN NEXT two;
        
 		WHILE i < arr LOOP
    	i := one + two;
        if i < arr then
         	RETURN NEXT i;
        end if;
    	one := two;
    	two := i;
    end loop;
 end;
$$
LANGUAGE 'plpgsql';
 
select * from fnc_fibonacci(100);
select * from fnc_fibonacci();