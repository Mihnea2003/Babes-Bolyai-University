using Microsoft.Extensions.Hosting;

namespace Web_practic_topics.Models
{
    public class Topic
    {
        public int Id { get; set; }
        public string TopicName { get; set; }
        public ICollection<Post> Posts { get; set; }
    }
}
