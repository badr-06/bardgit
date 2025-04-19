CREATE UNIQUE INDEX idx_person_discounts_unique on person_discounts(person_id, pizzeria_id);

-- для доказательства
set enable_seqscan =off;
EXPLAIN ANALYSE
SELECT discount from person_discounts
where pizzeria_id = 1