<?php
// PHP Highlighting Demo
// Ciel: co najviac tokenov pre testovanie temy.

// --- Strict types ---
declare(strict_types=1);

// --- Namespace, use, const ---
namespace App\Demo;

use DateTimeImmutable;
use Throwable;
use PDO;
use function strlen;
use const PHP_VERSION;

// --- Attributes (PHP 8) ---
#[\Attribute(\Attribute::TARGET_CLASS | \Attribute::TARGET_METHOD)]
class Route
{
    public function __construct(
        public string $method,
        public string $path
    ) {}
}

// --- Enum (PHP 8.1+) ---
enum Status: string
{
    case Draft = 'draft';
    case Published = 'published';
    case Archived = 'archived';
}

// --- Interface, trait, class ---
interface Loggable
{
    public function log(string $message): void;
}

trait Timestamps
{
    protected ?\DateTimeInterface $createdAt = null;
    protected ?\DateTimeInterface $updatedAt = null;

    public function touch(): void
    {
        $now = new DateTimeImmutable();
        $this->updatedAt ??= $now;
        $this->createdAt ??= $now;
    }
}

#[Route('GET', '/article')]
class Article implements Loggable
{
    use Timestamps;

    public function __construct(
        private int $id,
        private string $title,
        private string $content,
        private Status $status = Status::Draft,
    ) {}

    public function getTitle(): string
    {
        return $this->title;
    }

    public function isPublished(): bool
    {
        return $this->status === Status::Published;
    }

    public function log(string $message): void
    {
        echo "[LOG] {$message}\n";
    }
}

// --- Union / nullable / mixed types ---
function normalizeId(int|string|null $id): ?int
{
    if ($id === null) {
        return null;
    }

    if (is_string($id)) {
        $id = (int) $id;
    }

    return $id > 0 ? $id : null;
}

// --- Match expression ---
function statusLabel(Status $status): string
{
    return match ($status) {
        Status::Draft     => 'Draft',
        Status::Published => 'Published',
        Status::Archived  => 'Archived',
    };
}

// --- Anonymous function, arrow function, use ---
$sum = function (int ...$numbers): int {
    return array_reduce($numbers, fn(int $carry, int $n) => $carry + $n, 0);
};

$base = 10;
$adder = function (int $x) use ($base): int {
    return $base + $x;
};

// --- Arrays (indexed, asociativne, destructuring) ---
$numbers = [1, 2, 3, 4];
$user = [
    'id'    => 1,
    'name'  => 'Alice',
    'email' => 'alice@example.com',
];

['name' => $name, 'email' => $email] = $user;

// --- Stringy, heredoc, nowdoc ---
$single = 'single quoted';
$double = "double quoted with {$name}";
$heredoc = <<<TXT
Multi-line heredoc
User: {$name}
Email: {$email}
TXT;

$nowdoc = <<<'TXT'
Nowdoc string, variables are not expanded: {$name}
TXT;

// --- Null coalescing, ??= ---
$config = [];
$dbHost = $config['db_host'] ?? 'localhost';
$config['db_host'] ??= 'localhost';

// --- Control flow ---
for ($i = 0; $i < count($numbers); $i++) {
    if ($i === 2) {
        continue;
    }
}

foreach ($numbers as $index => $n) {
    if ($n === 3) {
        break;
    }
}

$i = 0;
while ($i < 3) {
    $i++;
}

do {
    $i--;
} while ($i > 0);

// --- Exceptions, try/catch/finally ---
function connectPdo(string $dsn): PDO
{
    try {
        $pdo = new PDO($dsn);
        $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
        return $pdo;
    } catch (Throwable $e) {
        error_log('PDO error: ' . $e->getMessage());
        throw $e;
    } finally {
        // placeholder for cleanup
    }
}

// --- Generators ---
function numbers(int $max): \Generator
{
    for ($i = 1; $i <= $max; $i++) {
        yield $i => $i * $i;
    }
}

// --- Main demo ---
function main(): void
{
    echo "PHP version: " . PHP_VERSION . PHP_EOL;

    $article = new Article(
        id: 1,
        title: 'Hello World',
        content: 'Lorem ipsum…',
        status: Status::Published,
    );

    $article->touch();
    $article->log('Article created: ' . $article->getTitle());

    echo 'Status label: ' . statusLabel(Status::Published) . PHP_EOL;
    echo 'Sum: ' . $sum = (fn(int ...$nums) => array_sum($nums))(1, 2, 3) . PHP_EOL;

    foreach (numbers(5) as $k => $v) {
        echo "square($k) = $v\n";
    }

    echo $heredoc . PHP_EOL;
    echo $nowdoc . PHP_EOL;

    $id = normalizeId('42');
    var_dump($id, $name, $email);
}

if (PHP_SAPI === 'cli') {
    main();
}
