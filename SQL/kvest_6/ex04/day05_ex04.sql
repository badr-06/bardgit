CREATE UNIQUE index idx_menu_unique on menu(pizzeria_id, pizza_name);

-- для доказательства
set enable_seqscan =off;
explain analyse
select pizza_name
from menu
where  pizzeria_id = 1;