CREATE UNIQUE INDEX idx_person_order_order_date on person_order(person_id, menu_id, order_date)
where order_date = date '2022-01-01';

-- для доказательства
set enable_seqscan =off;
explain analyse
SELECT person_id, menu_id from person_order
where order_date = date '2022-01-01'