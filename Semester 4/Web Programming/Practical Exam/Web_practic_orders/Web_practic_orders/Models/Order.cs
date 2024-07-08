namespace Web_practic_orders.Models
{
    public class Order
    {
        public int Id { get; set; }
        public string User { get; set; }
        public int ProductId { get; set; }
        public int Quantity { get; set; }
        public Product Product { get; set; }
    }
}
