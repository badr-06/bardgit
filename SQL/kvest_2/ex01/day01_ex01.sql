(SELECT name as object_name from person order by name )
UNION ALL
(SELECT pizza_name as object_name from menu order by pizza_name)