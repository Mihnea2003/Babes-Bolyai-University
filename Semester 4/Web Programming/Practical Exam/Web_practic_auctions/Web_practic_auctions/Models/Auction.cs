namespace Web_practic_auctions.Models
{
    public class Auction
    {
        public int Id { get; set; }
        public string User { get; set; }
        public int CategoryID { get; set; }
        public string Description { get; set; }
        public DateTime Date { get; set; }
        public Category Category { get; set; }
    }
}
