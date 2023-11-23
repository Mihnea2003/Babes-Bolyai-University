--1.Inserting in the Bosses Table
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(1,'Mihnea',9999);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(2,'Madalina',1000);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(5,'Badea',50);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(4,'Gabi',456);
INSERT INTO Bosses(boss_id,boss_name,balance)
VALUES(7,'Mike',99);
--2.Inserting in the Buyers Table
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(22,200,11.02,'Pipera');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(23,200,11.02,'Sighisoara');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(25,0,01.02,'Marasti');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(20,207,11.06,'Gheorgheni');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(12,250,05.90,'Cotroceni');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(662,600,10.00,'Marasti');
INSERT INTO Buyers(buyers_id,balance,birth_date,location)
VALUES(100,1200,07.08,'Gheorgheni');

--3.Inserting in the Shops Table
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(10,1,22,'Pipera','10:34:09 AM','22:34:09')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(11,2,22,'Cotroceni','10:00:00 AM','20:00:00')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(12,5,25,'Marasti','12:00:00 ','22:00:00')
INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
VALUES(13,4,100,'Gheorgheni','12:00:00 AM','19:00:00')

--INSERT INTO Shops(shops_id,boss_id,buyers_id,location,open_from,open_till)
--VALUES(10,4,100,'Gheorgheni','12:00:00 AM','19:00:00') error primary key
--4.Inserting in the Sites Table
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(33,100,500,'The first Site with more shops than you know') 
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(30,10,50,'This site has the best prices')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(31,30,150,'More shops than you will ever find')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(32,50,250,'The best in the industry')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(34,50,250,'The coziest shop')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(35,60,300,'The best of the best')
INSERT INTO Sites(sites_id,cappacity,cost_of_publicity,page_info)
VALUES(36,50,250,'If you dont find a shop on our site,will give you 50$')

--5.Inserting in the ExistIn Table
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(12,33);
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,34);
INSERT INTO ExistIn(shops_id,sites_id)
Values(10,30);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,32);
INSERT INTO ExistIn(shops_id,sites_id)
Values(12,36);
INSERT INTO ExistIn(shops_id,sites_id)
Values(13,32);
INSERT INTO ExistIn(shops_id,sites_id)
Values(11,34);
INSERT INTO ExistIn(shops_id,sites_id)
Values(13,35);
-- 6. Inserting into the Sellers Table
INSERT INTO Sellers(sellers_id, seller_name, location, birth_date, shops_id) VALUES
(1, 'Seller 1', 'Gheorgheni', '1990-01-15', 10),
(2, 'Seller 2', 'Marasti', '1985-03-20', 11),
(3, 'Seller 3', 'Bucuresti', '1995-07-10', 12),
(4, 'Seller 4', 'Sighisoara', '1980-11-25', 13),
(5, 'Seller 5', 'Gheorgheni', '1988-09-12', 10);

-- 7. Inserting into the Shoes Table
INSERT INTO Shoes(shoes_id, type, color, size, cost) VALUES
(1, 'Sneakers', 'Blue', 9, 50),
(2, 'Boots', 'Brown', 8, 65),
(3, 'Sandals', 'Black', 7, 40),
(4, 'Running Shoes', 'Red', 10, 55),
(5, 'Dress Shoes', 'Black', 9, 70);
INSERT INTO Shoes (shoes_id, type, color, size, cost)
VALUES (6, 'Sneakers', 'Red', 8, 60);

-- 8. Inserting into the Cleaning_sets Table
INSERT INTO Cleaning_sets(cleaning_sets_id, price, brand, efficiency) VALUES
(1, 25, 'Brand 1', 90),
(2, 30, 'Brand 2', 95),
(3, 20, 'Brand 3', 85),
(4, 35, 'Brand 4', 92),
(5, 28, 'Brand 5', 88);
UPDATE Cleaning_sets
SET price = 50
WHERE cleaning_sets_id = 1;

-- 9. Inserting into the HaveIt Table
INSERT INTO HaveIt(sellers_id, shoes_id) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5);

-- 10. Inserting into the PossessIt Table
INSERT INTO PossessIt(sellers_id, cleaning_sets_id) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(5, 5);

INSERT INTO Bosses (boss_id, boss_name, balance)
VALUES (6, 'New Boss', 5000);

-- Associating the boss with a shop (e.g., shop 14)
UPDATE Shops
SET boss_id = 6
WHERE shops_id = 14;

INSERT INTO Bosses (boss_id, boss_name, balance)
VALUES (199, 'Karl', 5000);

-- Inserting a shop and associating it with the boss
INSERT INTO Shops (shops_id, boss_id, buyers_id, location, open_from, open_till)
VALUES (149, 199, 22, 'Bucuresti', '08:00:00 AM', '18:00:00');
UPDATE Shops
SET boss_id = NULL
WHERE shops_id = 14;
--Deleting one Shoe and one Cleaning set
DELETE FROM Shoes
WHERE shoes_id = 3;

DELETE FROM Cleaning_sets
WHERE cleaning_sets_id = 2;

