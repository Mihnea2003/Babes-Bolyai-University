CREATE TABLE Buyers(
	buyers_id INT PRIMARY KEY,
	location VARCHAR(20),
	birth_date DATETIME,
	balance INT,
);
CREATE TABLE Bosses(
	boss_id INT PRIMARY KEY,
	balance INT,
	boss_name VARCHAR(20),
);

CREATE TABLE Shops(
	shops_id INT PRIMARY KEY,
	boss_id INT FOREIGN KEY
		REFERENCES Bosses(boss_id) UNIQUE,
	buyers_id INT FOREIGN KEY
		REFERENCES Buyers(buyers_id),
	location VARCHAR(15),
	open_from DATETIME,
	open_till DATETIME,
);
CREATE TABLE Sites(
	sites_id INT PRIMARY KEY,
	cappacity INT,
	page_info VARCHAR(50),
	cost_of_publicity INT,
);
CREATE TABLE ExistIn(
	shops_id INT FOREIGN KEY
		REFERENCES Shops(shops_id),
	sites_id INT FOREIGN KEY
		REFERENCES Sites(sites_id),
);
CREATE TABLE Sellers(
	sellers_id INT PRIMARY KEY,
	seller_name VARCHAR(50),
	location VARCHAR(20),
	birth_date DATETIME,
	shops_id INT FOREIGN KEY
		REFERENCES Shops(shops_id),
);
CREATE TABLE Shoes(
	shoes_id INT PRIMARY KEY,
	sellers_id INT FOREIGN KEY
		REFERENCES Sellers(sellers_id),
	type VARCHAR(15),
	color VARCHAR(10),
	size INT,
	cost INT
);
CREATE TABLE Cleaning_sets(
	cleaning_sets_id INT PRIMARY KEY,
	price INT,
	brand VARCHAR(20),
	sellers_id INT FOREIGN KEY
		REFERENCES Sellers(sellers_id),
	efficiency INT,
);
CREATE TABLE HaveIt(
	sellers_id INT FOREIGN KEY
		REFERENCES Sellers(sellers_id),
	shoes_id INT FOREIGN KEY
		REFERENCES Shoes(shoes_id),
);
CREATE TABLE PossessIt(
	sellers_id INT FOREIGN KEY
		REFERENCES Sellers(sellers_id),
	shoes_id INT FOREIGN KEY
		REFERENCES Cleaning_sets(cleaning_sets_id),
);


