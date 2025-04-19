--Session #1
BEGIN;
select rating from pizzeria where name like 'Pizza Hut';
update pizzeria set rating = 4 where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';

--Session #2
BEGIN;
select rating from pizzeria where name like 'Pizza Hut';
update pizzeria set rating = 3.6 where name like 'Pizza Hut';
commit;
select rating from pizzeria where name like 'Pizza Hut';
