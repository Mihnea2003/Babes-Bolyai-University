--a. 2 queries with the union operation; use UNION [ALL] and OR;
--1.Select The information of the buyers and shops where the location is in Gheorgheni or marasti
SELECT
    location AS Location,
    'Buyer' AS Type
FROM
    Buyers
WHERE
    location = 'Gheorgheni' OR location='Marasti'
UNION
SELECT
    location AS Location,
    'Shop' AS Type
FROM
    Shops
WHERE
    location = 'Gheorgheni' OR location = 'Marasti';
--2.Select Boss name and page_info  if the cost of the site is greater than 200 or lower than 100
Select boss_name  AS 'Information----------------------' from Bosses
UNION
SELECT page_info From Sites
WHERE cost_of_publicity>200 OR cost_of_publicity<100
--b. 2 queries with the intersection operation; use INTERSECT and IN;
--1.Select the common price between Shoes and Cleaning_sets
SELECT cost AS CommonCost
FROM Shoes
INTERSECT
SELECT price AS CommonCost
FROM Cleaning_sets;
--2.Select the cleaning sets that have a price less than 35 and efficiency greater than 85
SELECT cleaning_sets_id, price, efficiency
FROM Cleaning_sets
WHERE price < 35
AND cleaning_sets_id IN (
    SELECT cleaning_sets_id
    FROM Cleaning_sets
    WHERE efficiency > 85
);
--c. 2 queries with the difference operation; use EXCEPT and NOT IN;
--1.Select the shops that doesnt have any boss at the moment
SELECT shops_id, location
FROM Shops

EXCEPT

SELECT shops_id, location
FROM Shops
WHERE boss_id IS NOT NULL;
--2.Select the Shoes that the seller doesnt have it
SELECT shoes_id, type, color, size
FROM Shoes
WHERE shoes_id NOT IN (
    SELECT DISTINCT shoes_id
    FROM HaveIt
);
--d. 4 queries with INNER JOIN, LEFT JOIN, RIGHT JOIN, and FULL JOIN (one query per operator);
--one query will join at least 3 tables, while another one will join at least two many-to-many relationships;
--1.Retrieve information about shops and their respective bosses.
SELECT Shops.shops_id, Shops.location, Bosses.boss_name
FROM Shops
INNER JOIN Bosses ON Shops.boss_id = Bosses.boss_id;
--2.Retrieving information about sellers and the shops they are associated with,
--include sellers who are not associated with any shop.
SELECT Sellers.sellers_id, Sellers.seller_name, Shops.location
FROM Sellers
LEFT JOIN Shops ON Sellers.shops_id = Shops.shops_id;
--3.Retrieving information about buyers and the shops they are associated with,if a shop is not associated 
--with any boss,still list it
SELECT Buyers.buyers_id, Buyers.location, Shops.location
FROM Buyers
RIGHT JOIN Shops ON Buyers.buyers_id = Shops.buyers_id;
--4.find information about sellers, their associated shoes, and their associated cleaning sets.
SELECT 
    s.sellers_id, 
    s.seller_name, 
    sh.type AS Shoe_Type, 
    cs.brand AS CleaningSet_Brand
FROM Sellers s
FULL JOIN HaveIt h ON s.sellers_id = h.sellers_id
LEFT JOIN Shoes sh ON h.shoes_id = sh.shoes_id
FULL JOIN PossessIt p ON s.sellers_id = p.sellers_id
LEFT JOIN Cleaning_sets cs ON p.cleaning_sets_id = cs.cleaning_sets_id;

--e. 2 queries with the IN operator and a subquery in the WHERE clause; in at least one case, 
--the subquery must include a subquery in its own WHERE clause;
--1.Select buyers that have made a purchase in Gheorgheni or Bucuresti
SELECT *
FROM Buyers
WHERE buyers_id IN (
    SELECT DISTINCT buyers_id
    FROM Shops
    WHERE location = 'Gheorgheni' OR location = 'Bucuresti'
);
--2.Select Shops that have a maximum capacity on sites
Select *
From Shops
Where shops_id IN(
	SELECT shops_id
	FROM ExistIn
	WHERE sites_id IN (
		SELECT sites_id
		FROM Sites
		WHERE cappacity >= (
			SELECT MAX(cappacity)
			FROM Sites
		)
	)
);
--f. 2 queries with the EXISTS operator and a subquery in the WHERE clause;
--1.Select different shops that have associated just one seller
SELECT DISTINCT S.*
FROM Shops AS S
WHERE EXISTS (
    SELECT 1
    FROM Sellers AS Se
    WHERE Se.shops_id = S.shops_id
);
--2.Select buyers who made at least one purchase at a shop and orders the results by the location of the buyers
SELECT DISTINCT B.*
FROM Buyers AS B
WHERE EXISTS (
    SELECT 1
    FROM Shops AS Sh
    WHERE Sh.buyers_id = B.buyers_id
)
ORDER BY B.balance;
--g. 2 queries with a subquery in the FROM clause;   
--1.Select the boss and his shop,ordered by their balance
SELECT S.shops_id, S.location, B.boss_name , B.balance
FROM Shops S
JOIN Bosses B ON S.boss_id = B.boss_id
ORDER BY B.balance;
--2.Select the information of the shops and the number of buyers
SELECT S.shops_id, S.location, B.boss_name, COUNT(S.buyers_id) AS number_of_buyers
FROM Shops S
LEFT JOIN Bosses B ON S.boss_id = B.boss_id
LEFT JOIN Buyers Bu ON S.buyers_id = Bu.buyers_id
GROUP BY S.shops_id, S.location, B.boss_name;
--h. 4 queries with the GROUP BY clause, 3 of which also contain the HAVING clause; 
--2 of the latter will also have a subquery in the HAVING clause; 
--use the aggregation operators: COUNT, SUM, AVG, MIN, MAX;
--1.Select shops and their total sales
SELECT S.shops_id, S.location, SUM(SH.cost) AS total_sales_amount
FROM Shops S
LEFT JOIN Sellers SR ON S.shops_id = SR.shops_id
LEFT JOIN HaveIt HI ON SR.sellers_id = HI.sellers_id
LEFT JOIN Shoes SH ON HI.shoes_id = SH.shoes_id
GROUP BY S.shops_id, S.location;
--2.Select buyers that spent more than 40 dollars
SELECT B.buyers_id, B.location, SUM(SH.cost) AS total_purchase_amount
FROM Buyers B
LEFT JOIN Shops S ON B.buyers_id = S.buyers_id
LEFT JOIN Sellers SR ON S.shops_id = SR.shops_id
LEFT JOIN HaveIt HI ON SR.sellers_id = HI.sellers_id
LEFT JOIN Shoes SH ON HI.shoes_id = SH.shoes_id
GROUP BY B.buyers_id, B.location
HAVING SUM(SH.cost) > 40;
--3.Select sellers average shoe cost that is not between 50 and 100 dollars
SELECT S.sellers_id, S.seller_name, CS.efficiency, AVG(SH.cost) AS avg_shoe_cost
FROM Sellers S
JOIN HaveIt HI ON S.sellers_id = HI.sellers_id
JOIN Shoes SH ON HI.shoes_id = SH.shoes_id
JOIN PossessIt PI ON S.sellers_id = PI.sellers_id
JOIN Cleaning_sets CS ON PI.cleaning_sets_id = CS.cleaning_sets_id
GROUP BY S.sellers_id, S.seller_name, CS.efficiency
HAVING AVG(SH.cost) > 100 OR AVG(SH.cost) < 50;
--4.Show shops with a summary of the number of buyers in each shop with high and low balances
SELECT S.shops_id, S.location,
       COUNT(CASE WHEN B.balance > 100 THEN B.buyers_id END) AS high_balance_buyers,
       COUNT(CASE WHEN B.balance <= 100 THEN B.buyers_id END) AS low_balance_buyers
FROM Shops S
LEFT JOIN Buyers B ON S.buyers_id = B.buyers_id
GROUP BY S.shops_id, S.location;
--i. 4 queries using ANY and ALL to introduce a subquery in the WHERE clause (2 queries per operator);
--rewrite 2 of them with aggregation operators, and the other 2 with IN / [NOT] IN.
--1.Select the sellers that have shoes prices greater than cleaning sets prices
SELECT S.sellers_id, S.seller_name
FROM Sellers S
WHERE S.sellers_id = ANY (SELECT H.sellers_id FROM HaveIt H
                          JOIN Shoes SH ON H.shoes_id = SH.shoes_id
                          WHERE SH.cost > ANY (SELECT CS.price FROM Cleaning_sets CS));
--2. List Shops with Buyers Who Have the Highest Balance
SELECT *
FROM Shops S
WHERE S.buyers_id = ANY (SELECT B.buyers_id
                        FROM Buyers B
                        WHERE B.balance = (SELECT MAX(balance) FROM Buyers));
--3.same as the above one
SELECT *
FROM Shops S
WHERE S.buyers_id = ALL (SELECT B.buyers_id
                        FROM Buyers B
                        WHERE B.balance = (SELECT MAX(balance) FROM Buyers));
--4.Select the seller that have the most priced shoe
SELECT TOP 1 S.sellers_id, S.seller_name
FROM Sellers S
WHERE S.sellers_id = ALL (SELECT sellers_id
                          FROM Shoes
                          WHERE cost >= ALL (SELECT cost FROM Shoes));
--5.the first exercise but with aggregation operator
SELECT S.sellers_id, S.seller_name
FROM Sellers S
WHERE S.sellers_id = ANY (
  SELECT H.sellers_id
  FROM HaveIt H,Shoes SH,PossessIt P
  WHERE SH.cost > (SELECT MIN(CS.price) FROM Cleaning_sets CS WHERE CS.cleaning_sets_id = P.cleaning_sets_id)
);
--6.exercise 2 but with aggregation operator
SELECT S.*
FROM Shops S
WHERE S.buyers_id = ANY (
  SELECT B.buyers_id
  FROM Buyers B
  WHERE B.balance = (SELECT MAX(balance) FROM Buyers)
);
--7.exercise 3 using NOT IN
SELECT *
FROM Shops S
WHERE S.buyers_id NOT IN (
    SELECT B.buyers_id
    FROM Buyers B
    WHERE B.balance < (SELECT MAX(balance) FROM Buyers)
);
--8.exercise 4 with operator IN
SELECT TOP 1 S.sellers_id, S.seller_name
FROM Sellers S
WHERE S.sellers_id IN (
    SELECT sellers_id
    FROM Shoes
    WHERE cost = (SELECT MAX(cost) FROM Shoes)
);


