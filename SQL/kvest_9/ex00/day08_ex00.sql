--Session #1
BEGIN;
UPDATE pizzeria set rating = 5 where name = 'Pizza Hut';
SELECT * from pizzeria WHERE name like 'Pizza Hut'

--Session #2
SELECT * from pizzeria WHERE name like 'Pizza Hut'

--Session #1
COMMIT;

--Session #2
SELECT * from pizzeria WHERE name like 'Pizza Hut'
