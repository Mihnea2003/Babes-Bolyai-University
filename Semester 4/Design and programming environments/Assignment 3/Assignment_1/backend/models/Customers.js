/* eslint-disable no-undef */
class Customer {
    constructor(id, name) {
      this._id = id;
      this._name = name;
      this._shoes = [];
    }
  
    get id() {
      return this._id;
    }
  
    get name() {
      return this._name;
    }
  
    get shoes() {
      return this._shoes;
    }
  
    addShoe(shoe) {
      this._shoes.push(shoe);
    }
  
    removeShoe(shoe) {
      const index = this._shoes.indexOf(shoe);
      if (index !== -1) {
        this._shoes.splice(index, 1);
      }
    }
  
    toString() {
      let shoeList = '';
      this._shoes.forEach((shoe) => {
        shoeList += shoe.toString();
      });
      return `Customer: ID: ${this._id} Name: ${this._name} Email: ${this._email}\nShoes:\n${shoeList}`;
    }
  }
  
  module.exports = Customer;
  