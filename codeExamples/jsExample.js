// JavaScript Highlighting Demo
// This file demonstrates as many JS/ES features as possible for syntax highlighting.

// --- Comments ---
// Single-line comment
/* Multi-line comment */

// --- Variables and constants ---
let x = 10;
const PI = 3.14159;
var legacy = 'old';

// --- Data types ---
let str = "Hello";
let num = 123.45;
let bool = true;
let undef = undefined;
let n = null;
let sym = Symbol('sym');
let big = 1234567890123456789012345678901234567890n;

// --- Objects and arrays ---
const obj = {
  name: 'Alice',
  age: 30,
  active: true,
  address: {
    city: 'Bratislava',
    zip: '81101'
  }
};

const arr = [1, 2, 3, 'four', { five: 5 }];

// --- Template literals ---
let greeting = `Hello, ${obj.name}! You are ${obj.age} years old.`;

// --- Functions ---
function add(a, b) {
  return a + b;
}

const multiply = (a, b) => a * b;

(function immediate() {
  console.log('IIFE executed');
})();

// --- Classes and inheritance ---
class Person {
  static species = 'Human';

  #privateField = 42;

  constructor(name, age) {
    this.name = name;
    this.age = age;
  }

  greet() {
    console.log(`Hi, I'm ${this.name}`);
  }

  get secret() {
    return this.#privateField;
  }
}

class Employee extends Person {
  constructor(name, age, role) {
    super(name, age);
    this.role = role;
  }

  work() {
    console.log(`${this.name} is working as ${this.role}`);
  }
}

// --- Destructuring ---
const { name, age } = obj;
const [first, second] = arr;

// --- Spread and rest operators ---
const copy = { ...obj, id: 123 };
const nums = [1, 2, 3];
function sum(...args) {
  return args.reduce((a, b) => a + b, 0);
}

// --- Modules (ESM syntax) ---
// export function exportedFn() {}
// import { exportedFn } from './module.js';

// --- Promises and async/await ---
function asyncTask() {
  return new Promise((resolve, reject) => {
    setTimeout(() => resolve('done'), 1000);
  });
}

async function run() {
  try {
    const result = await asyncTask();
    console.log('Result:', result);
  } catch (err) {
    console.error('Error:', err);
  }
}

run();

// --- Control flow ---
for (let i = 0; i < 3; i++) {
  if (i === 1) continue;
  console.log(i);
}

let j = 0;
while (j < 3) {
  j++;
}

do {
  j--;
} while (j > 0);

switch (x) {
  case 5:
    console.log('Five');
    break;
  case 10:
    console.log('Ten');
    break;
  default:
    console.log('Other');
}

// --- Exceptions ---
try {
  throw new Error('Something went wrong');
} catch (e) {
  console.warn('Caught:', e.message);
} finally {
  console.log('Always runs');
}

// --- Iterators and generators ---
function* gen() {
  yield 1;
  yield 2;
  yield 3;
}

for (const value of gen()) {
  console.log(value);
}

// --- Maps, Sets, WeakMap, WeakSet ---
const map = new Map();
map.set('a', 1);

const set = new Set([1, 2, 3]);

const weakMap = new WeakMap();
const weakSet = new WeakSet();

// --- Optional chaining and nullish coalescing ---
const city = obj.address?.city ?? 'Unknown';

// --- Regular expressions ---
const regex = /([A-Z])\w+/gi;
console.log('Test', regex.test('Hello World'));

// --- JSON and date ---
const json = JSON.stringify(obj, null, 2);
const parsed = JSON.parse(json);
const now = new Date();

// --- DOM demo (only visible in browsers) ---
if (typeof document !== 'undefined') {
  const div = document.createElement('div');
  div.textContent = 'Hello DOM';
  document.body.appendChild(div);
}

// --- ES2020+ features ---
const optional = obj.nonexistent?.prop;
const val = obj.value ?? 'default';
const entries = Object.entries(obj);
const fromEntries = Object.fromEntries(entries);

// --- BigInt and numeric separators ---
const bigNum = 1_000_000_000_000n;

// --- Logical assignment ---
let flag = false;
flag ||= true;
flag &&= false;
flag ??= true;

// --- WeakRef and FinalizationRegistry ---
const registry = new FinalizationRegistry((heldValue) => {
  console.log('Finalized:', heldValue);
});

// --- Top-level await (ES2022) ---
// Uncomment if your environment supports it
// const result = await asyncTask();

// --- Output ---
console.log({ PI, obj, arr, greeting, city, json });
