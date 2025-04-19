SELECT pm.name from v_persons_male pm
UNION 
SELECT pf.name from v_persons_female pf
order BY 1