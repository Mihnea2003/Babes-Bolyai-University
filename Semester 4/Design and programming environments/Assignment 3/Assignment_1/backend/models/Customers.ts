import { Shoe } from "./Shoes";

export class Customer {
    private _id: number;
    private _name: string;
    private _shoes: Shoe[];
  
    constructor(id: number, name: string) {
      this._id = id;
      this._name = name;
      this._shoes = [];
    }
  
    get id(): number {
      return this._id;
    }
  
    get name(): string {
      return this._name;
    }
  
    get shoes(): Shoe[] {
      return this._shoes;
    }
  
    addShoe(shoe: Shoe): void {
      this._shoes.push(shoe);
    }
  
    removeShoe(shoe: Shoe): void {
      const index = this._shoes.indexOf(shoe);
      if (index !== -1) {
        this._shoes.splice(index, 1);
      }
    }
  }
  