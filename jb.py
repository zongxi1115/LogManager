import pyppeteer
import pyppeteer_stealth
import asyncio

# name = "王宗喜"
# no = "240602143"
# col = "信息工程"
# className = "软件2402"
do_list = [
    # {
    #     'name':'杨嘉璐',
    #     'no':'243303136',
    #     'col':'电气',
    #     'className':'新能源2402',
    # },
      {
        'name':'余家伟',
        'no':'243303139',
        'col':'电气',
        'className':'新能源2402',
    }
]


async def main():
    # 指定路径
    browswer = await pyppeteer.launch(
        executablePath="C:\Program Files (x86)\Microsoft\Edge\Application\msedge.exe",
        headless=False,
        useDataDir='./userdata'
        #   userDataDir='./user_data'
    )
    page = await browswer.newPage()
    await page.goto("https://mp.yiban.cn/app/login/")
    # await page.waitForNavigation()
    await page.waitForSelector(".mdc-text-field__input")
    # await page.type(".mdc-text-field__input","123456789")
    # await page.type(".mdc-text-field__input")
    inputs = await page.querySelectorAll(".mdc-text-field__input")
    await inputs[0].type("school_yzdx@yiban.cn")
    await inputs[1].type("School_yzdx2022")
    await asyncio.sleep(0.5)
    await page.click("button.mdc-button")
    await asyncio.sleep(2)
    await page.goto("https://mp.yiban.cn/app/org-certification/list/2003686")
    # 等待页面加载
    await page.waitForSelector(".mdc-text-field__input")
    inputs = await page.querySelectorAll(".mdc-text-field__input")
    # 预先注入$定义
    await page.evaluate("""() => {
        window.$ = document.querySelector.bind(document);
    }""")
    for i in do_list:
        await inputs[1].type(i['name'])
        await inputs[3].type(i['no'])
        await asyncio.sleep(0.5)
        btns = await page.querySelectorAll("button.mdc-button")
        await btns[2].click()
        editBtn = ".row-action.link"
        await page.waitForSelector(editBtn)
        await page.click(editBtn)
        orgBtn = ".org-node-tree-container input"
        await page.waitForSelector(orgBtn)
        await page.click(orgBtn)
        tree_node = ".mdc-tree-node"
        await asyncio.sleep(2)
        tree_node = await page.querySelector(tree_node)
        

        js = (
            """() => {
            [...$('.mdc-tree-node').querySelectorAll('li')].filter(i=>i.innerHTML.indexOf('"""
            + i['col']
            + """')!=-1)[0].querySelector('i').click()
        }"""
        )
        await page.evaluate(js)
        await asyncio.sleep(1.5)
        js = """()=>{[...[...$('.mdc-tree-node').querySelectorAll('li')].filter(i=>i.innerHTML.indexOf('""" + i['className'] + """')!=-1)[0].querySelectorAll('li')].filter(i=>i.innerHTML.indexOf('""" + i['className'] + """')!=-1)[0].querySelector('label').click()}"""
        await page.evaluate(js)
        await asyncio.sleep(0.5)
        submitBtn = await page.querySelectorAll(".mdc-button")
        await submitBtn[11].click()
        await asyncio.sleep(1)


    await asyncio.sleep(10)


# start

if __name__ == "__main__":
    asyncio.get_event_loop().run_until_complete(main())
