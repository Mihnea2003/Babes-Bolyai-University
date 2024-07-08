namespace Web_practic_journals.Models
{
    public class Article
    {
        public int Id { get; set; }
        public string User { get; set; }
        public int JournalId { get; set; }
        public string Summary { get; set; }
        public DateTime Date { get; set; }

        public virtual Journal Journal { get; set; }
    }
}
