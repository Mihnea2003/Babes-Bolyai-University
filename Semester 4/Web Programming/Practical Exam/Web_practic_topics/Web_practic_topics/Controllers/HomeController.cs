using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using System.Diagnostics;
using System.Linq;
using System.Threading.Tasks;
using Web_practic_topics.Data;
using Web_practic_topics.Models;

namespace Web_practic_topics.Controllers
{
    public class HomeController : Controller
    {
        private readonly ILogger<HomeController> _logger;
        private readonly ApplicationDbContext _context;

        public HomeController(ILogger<HomeController> logger, ApplicationDbContext context)
        {
            _logger = logger;
            _context = context;
        }

        public IActionResult Index()
        {
            return View();
        }

        [HttpPost]
        public IActionResult SetUsername(string username)
        {
            TempData["Username"] = username;
            return RedirectToAction(nameof(Topics));
        }

        public async Task<IActionResult> Topics()
        {
            var topics = await _context.Topics.Include(t => t.Posts).ToListAsync();
            return View(topics);
        }

        public async Task<IActionResult> Posts(int topicId)
        {
            var topic = await _context.Topics.Include(t => t.Posts).FirstOrDefaultAsync(t => t.Id == topicId);
            if (topic == null)
            {
                return NotFound();
            }
            return View(topic);
        }

        [HttpPost]
        public async Task<IActionResult> AddPost(int topicId, string text)
        {
            var username = TempData["Username"]?.ToString();
            if (string.IsNullOrEmpty(username))
            {
                return RedirectToAction(nameof(Index));
            }

            var topic = await _context.Topics.FindAsync(topicId);
            if (topic == null)
            {
                topic = new Topic { TopicName = $"New Topic ({topicId})" }; // You can customize the topic name here
                _context.Topics.Add(topic);
                await _context.SaveChangesAsync();
            }

            var post = new Post
            {
                User = username,
                TopicId = topic.Id,
                Text = text,
                Date = DateTime.Now
            };

            _context.Posts.Add(post);
            await _context.SaveChangesAsync();

            TempData["Username"] = username;
            TempData["Message"] = "New post added successfully!"; // Add a message to TempData

            return RedirectToAction(nameof(Posts), new { topicId = topic.Id });
        }

        [HttpPost]
        public async Task<IActionResult> UpdatePost(int postId, string newText)
        {
            var username = TempData["Username"]?.ToString();
            if (string.IsNullOrEmpty(username))
            {
                return RedirectToAction(nameof(Index));
            }

            var post = await _context.Posts.FindAsync(postId);
            if (post == null)
            {
                return NotFound();
            }

            post.Text = newText;
            post.User = username;
            post.Date = DateTime.Now;

            _context.Posts.Update(post);
            await _context.SaveChangesAsync();

            TempData["Username"] = username;  // Retain username across requests

            return RedirectToAction(nameof(Posts), new { topicId = post.TopicId });
        }

        [HttpPost]
        public async Task<IActionResult> AddTopic(string topicName)
        {
            var username = TempData["Username"]?.ToString();
            if (string.IsNullOrEmpty(username))
            {
                return RedirectToAction(nameof(Index));
            }

            var topic = await _context.Topics.FirstOrDefaultAsync(t => t.TopicName == topicName);
            if (topic == null)
            {
                topic = new Topic { TopicName = topicName };
                _context.Topics.Add(topic);
                await _context.SaveChangesAsync();
            }

            TempData["Username"] = username;  // Retain username across requests

            return RedirectToAction(nameof(Posts), new { topicId = topic.Id });
        }

        public IActionResult Privacy()
        {
            return View();
        }

        [ResponseCache(Duration = 0, Location = ResponseCacheLocation.None, NoStore = true)]
        public IActionResult Error()
        {
            return View(new ErrorViewModel { RequestId = Activity.Current?.Id ?? HttpContext.TraceIdentifier });
        }
    }
}
