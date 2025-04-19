--Session #1
begin transaction isolation level serializable;
update pizzeria set rating = 1 where id = 1;
update pizzeria set rating = 1 where id = 2;
commit;

--Session #1
begin transaction isolation level serializable;
update pizzeria set rating = 2 where id = 2;
update pizzeria set rating = 2 where id = 1;
commit;